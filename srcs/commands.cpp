/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:02:49 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/24 15:45:49 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/commands.hpp"

int call_command(Server &serv, User &u, std::vector<std::string> message)
{
	if (message.size() == 0)
		return (-1);
	std::cerr << YELLOW << "command received: " << message[0] << ENDL;


	if (message[0] == "NICK")
		return (NICK(serv, u, message));
	else if (message[0] == "QUIT")
		return (QUIT(serv, u, message));
	else if (message[0] == "USER")
		return (USER(serv, u, message));

	else if (message[0] == "PONG")
	{
		std::cout << "Received PONG: Silencing command" << ENDL;
		return (0);
	}
	else if (message[0] == "PING")
		return (PING(serv, u, message));

	else if (u.get_nickname() == "" || u.get_username() == "")
	{
		send_reply(CODE_ERR_NOTREGISTERED, serv, u, message);
		return (1);
	}
	else if (message[0] == "AWAY")
		return (AWAY(serv, u, message));
	else if (message[0] == "JOIN")
		return (JOIN(serv, u, message));
	else if (message[0] == "LUSERS")
		return (LUSERS(serv, u, message));
	else if (message[0] == "MOTD")
		return (MOTD(serv, u, message));
	else if (message[0] == "NOTICE")
		return (NOTICE(serv, u, message));
	else if (message[0] == "PART")
		return (PART(serv, u, message));
	else if (message[0] == "PRIVMSG")
		return (PRIVMSG(serv, u, message));
	else if (message[0] == "WHOIS")
		return (WHOIS(serv, u, message));
	else if (message[0] == "OPER")
		return (OPER(serv, u, message));
	else if (message[0] == "PASS")
		return (PASS(serv, u, message));
	else if (message[0] == "ISON")
		return (ISON(serv, u, message));

	std::cerr << RED << "Error: Command not found" << ENDL;
	send_reply(CODE_ERR_UNKNOWNCOMMAND, serv, u, message);
	return (-404);
}

int greeting(Server &s, User &u, std::vector<std::string> message)
{
	LUSERS(s, u, message);
	MOTD(s, u, message);
	return (0);
}

int AWAY(Server &serv, User &u, std::vector<std::string> message)
{
	if (message.size() == 1)
	{
		u.set_awaymsg("");
		u.get_modes().set_a(false);
		send_reply(CODE_RPL_UNAWAY, serv, u, message);
	}
	else
	{
		u.set_awaymsg(message[1].substr(1));
		u.get_modes().set_a(true);
		send_reply(CODE_RPL_NOWAWAY, serv, u, message);
	}
	return (0);
}

std::vector<std::string> split_on(std::string str, char limit)
{
	std::vector<std::string> res;
	int i;
	std::list<int> l;
	std::list<int>::iterator begin, end;

	//find separators
	l.push_back(-1);
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == limit)
			l.push_back(i);
		i++;
	}
	l.push_back(i);
	res.reserve(l.size());

	begin = l.begin();
	end = l.end();
	end--;

	i = 0;
	while (begin != end)
	{
		res.push_back(str.substr(*begin + 1, *(++begin)));
	}
	return (res);
	//buffer will now point after the \r\n.
}

int joining_procedure(Server &serv, User &u, std::vector<std::string> message, Channel &c, std::string password = "")
{
	std::vector<std::string> other(4, "");
	std::string msg = "";

	other[0] = c.str_name();

	if (c.get_modes().get_l() == true && c.get_users().size()) // size limit
	{
		send_reply(CODE_ERR_CHANNELISFULL, serv, u, message, other);
		return (1);
	}
	/*
	TODO invite command
	if (c.get_modes().get_i() && !(c.is_invited(u)))
	{
		send_reply(CODE_ERR_INVITEONLYCHAN, serv, u, message);
		return (2);
	}
	*/
	if (c.is_user_banned(u))
	{
		send_reply(CODE_ERR_BANNEDFROMCHAN, serv, u, message, other);
		return (3);
	}
	/*
	TODO check channel key
	if (password == c.get_password())
	{
		send_reply(CODE_ERR_BADCHANNELKEY, serv, u, message);
		return (4);
	}
	*/
	(void)password;

	//nothing wrong, can connect !

	c.add_user(&u);
	u.add_channel(&c);

	msg = ":" + u.full_id() + " JOIN " + c.get_prefix() + c.get_name() + "\r\n";
	c.send(serv, msg);
	
	//topic
	other[0] = c.str_name();
	other[1] = c.get_topic();

	send_reply(CODE_RPL_TOPIC, serv, u, message, other);
	//users

	//TODO replace with the name command once done
	other[1] = "";

	for (std::list<User*>::iterator begin = c.get_users().begin(); begin != c.get_users().end(); ++begin)
	{
		if ((*begin)->get_modes().get_O())
			other[1] += "@";
		other[1] += (*begin)->get_nickname() + " ";
	}
	other[1] = other[1].substr(0, other[1].size());
	send_reply(CODE_RPL_NAMREPLY, serv, u, message, other);
	send_reply(CODE_RPL_ENDOFNAMES, serv, u, message, other);

	return (0);
}

bool channel_name_validity(std::string name)
{
	int i;

	if (name.length() < 2 ||
		(name[0] != '#' && name[0] != '!' && name[0] != '+' && name[0] != '&') ||
		name.length() > 50)
		return (false);

	i = 1;
	while (name[i] != '\0')
	{
		if (name[i] == ' ' || name[i] == ',' || name[i] == 7)
			return (false);
		i++;
	}
	return (true);
}

std::list<Channel>::iterator create_channel(Server &serv, std::string name, std::string password)
{
	return (serv.add_channel(name, password));
}

int selecting_server(Server &serv, User &u, std::vector<std::string> message, std::vector<std::string> channels, std::vector<std::string> passwords)
{
	std::vector<std::string>::iterator p_begin, p_end, c_begin, c_end;
	std::list<Channel>::iterator begin, end, c_new;
	std::vector<std::string> other(8, "");
	bool used;

	c_begin = channels.begin();
	c_end = channels.end();
 
	p_begin = passwords.begin();
	p_end = passwords.end();
	
	while (c_begin != c_end)
	{
		if (!(channel_name_validity(*c_begin)))
		{
			other[0] = (*c_begin);
			send_reply(CODE_ERR_NOSUCHCHANNEL, serv, u, message, other);
			c_begin++;
			if (p_begin != p_end)
				p_begin++;
			continue;
		}
		begin = serv.get_channels().begin();
		end = serv.get_channels().end();
		used = false;
		while (begin != end && !(used))
		{
			if ((*begin).str_name() == *c_begin)
			{
				used = true;
				
				if (u.get_nb_channels() >= MAX_CHANNELS)
				{
					other[0] = 
					send_reply(CODE_ERR_TOOMANYCHANNELS, serv, u, message, other);
					break ;
				}
				joining_procedure(serv, u, message, (*begin));
			}
			begin++;
		}
		if (used == false)
		{
			// TODO Create Channel
			CYELLOW << "Creating channel " << *c_begin << ENDL;
			c_new = create_channel(serv, *c_begin, (p_begin != p_end ? (*p_begin) : ""));
			CGREEN << "Channel " << *c_begin << " created" << ENDL;
			joining_procedure(serv, u, message, (*c_new), (p_begin != p_end ? (*p_begin) : ""));
		}
		c_begin++;
		if (p_begin != p_end)
			p_begin++;
	}
	return (0);
}

int JOIN(Server &serv, User &u, std::vector<std::string> message)
{
	std::list<Channel>::iterator pos;
	std::vector<std::string> part_message;
	std::vector<std::string> channels(0);
	std::vector<std::string> passwords(0);
	std::list<Channel>::iterator begin, end;

	if (message.size() == 1)
	{
		send_reply(CODE_ERR_NEEDMOREPARAMS, serv, u, message);
		return (1);
	}
	else if (message.size() > 3)
	{
		//TODO: too many params
		return (3);
	}
	else if (message.size() == 2 && message[1] == "0")
	{
		part_message[0] = "PART";
		begin = serv.get_channels().begin();
		end = serv.get_channels().end();
		while (begin != end)
		{
			if ((*begin).has_user(&u))
			{
				part_message[1] = (*begin).get_name();
				//TODO PART(serv, u, message);
			}
			begin++;
		}
		return (1); // TODO set return
	}
	else
	{
		channels = split_on(message[1], ',');
		if (message.size() == 3)
			passwords = split_on(message[2], ',');
		return (selecting_server(serv, u, message, channels, passwords));
	}

/*
	ERR_NEEDMOREPARAMS
	ERR_BANNEDFROMCHAN
	ERR_INVITEONLYCHAN
	ERR_BADCHANNELKEY
	ERR_CHANNELISFULL
ERR_BADCHANMASK
	ERR_NOSUCHCHANNEL
	ERR_TOOMANYCHANNELS
ERR_TOOMANYTARGETS: using short bname and multpile answers
ERR_UNAVAILRESOURCE
RPL_TOPIC
RPL_NAMREPLY
*/

}

int LUSERS(Server &s, User &u, std::vector<std::string> message)
{
	send_reply(CODE_RPL_WELCOME, s, u, message);
	send_reply(CODE_RPL_YOURHOST, s, u, message);
	//send_reply(CODE_RPL_CREATED, s, u, message);
	send_reply(CODE_RPL_MYINFO, s, u, message);
	send_reply(CODE_RPL_LUSERME, s, u, message);
	return (0);
}

int MOTD(Server &serv, User &u, std::vector<std::string> message)
{
	if (serv.get_motd() == "")
	{
		send_reply(CODE_ERR_NOMOTD, serv, u, message);
		return (-1);
	}
	else
	{
		send_reply(CODE_RPL_MOTD, serv, u, message);
		send_reply(CODE_RPL_MOTDSTART, serv, u, message);
		send_reply(CODE_RPL_ENDOFMOTD, serv, u, message);
		return (0);
	}
}

int NICK(Server &serv, User &u, std::vector<std::string> message)
{
	if (message.size() < 2)
	{
		send_reply(CODE_ERR_NONICKNAMEGIVEN, serv, u, message);
		return (1);
	}
	if (serv.getuserbynick(message[1]))
	{
		send_reply(CODE_ERR_NICKNAMEINUSE, serv, u, message);
		return (2);
	}
	else
	{
		if (u.get_nickname() == "" && u.get_username() != "")
		{
			u.set_nickname(message[1]);
			greeting(serv, u, message);
		}
		else
		{
			u.set_nickname(message[1]);
		}
	}
	return (0);
}

int NOTICE(Server &serv, User &u, std::vector<std::string> message)
{
	User *recipient;
	std::string nick;
	size_t occ_e, occ_a, occ_p;
	std::string rep;
	int i;

	if (message.size() == 1)
	{
		send_reply(CODE_ERR_NORECIPIENT, serv, u, message);
		return (-1);
	}
	else if (message.size() == 2)
	{
		send_reply(CODE_ERR_NOTEXTTOSEND, serv, u, message);
		return (-2);
	}

	//TODO channels

	occ_e = message[1].find("!");
	occ_a = message[1].find("@");
	occ_p = message[1].find("%");

	if (occ_e != (unsigned long)(-1) && occ_e < occ_a && occ_e < occ_p)
	{
		nick = message[1].substr(0, occ_e);
		recipient = serv.getuserbynick(nick);
	}
	else if (occ_a != (unsigned long)(-1) && occ_a < occ_e && occ_a < occ_p)
	{
		nick = message[1].substr(0, occ_a);
		recipient = serv.getuserbynick(nick);
	}
	else if (occ_p != (unsigned long)(-1) && occ_p < occ_e && occ_p < occ_a)
	{
		nick = message[1].substr(0, occ_p);
		recipient = serv.getuserbynick(nick);
	}
	else
		recipient = serv.getuserbynick(message[1]);
	
	if (recipient == NULL)
	{
		send_reply(CODE_ERR_NOSUCHNICK, serv, u, message);
		return (-3);
	}
	else
	{
		rep = ":" + u.get_nickname() + "!" + u.get_username() + "@" + u.get_hostname() +\
		 message[0] + " " + message[1] + " " + (message[2]) + "\r\n";
		//serv.write_socket(u.get_fd(), rep);
		std::cerr << MAG << ":recipient: " << recipient->get_nickname() << ENDL;
		i = serv.write_socket(recipient->get_fd(), rep);
		std::cerr << recipient->get_nickname() << " > " + rep;
		return (i);
	}
}

int PRIVMSG(Server &serv, User &u, std::vector<std::string> message)
{
	User *recipient;
	std::string nick;
	size_t occ_e, occ_a, occ_p;
	std::string rep;
	std::vector<std::string> targets;
	int i;

	if (message.size() == 1)
	{
		send_reply(CODE_ERR_NORECIPIENT, serv, u, message);
		return (-1);
	}
	else if (message.size() == 2)
	{
		send_reply(CODE_ERR_NOTEXTTOSEND, serv, u, message);
		return (-2);
	}

	//TODO channels

	targets = split_on(message[1], ',');

	for (std::vector<std::string>::iterator target = targets.begin(); target != targets.end(); target++)
	{

		if ((*target)[0] == '!' ||
			(*target)[0] == '#' ||
			(*target)[0] == '&' ||
			(*target)[0] == '+') // is channel
		{
			for (std::list<Channel>::iterator chan = serv.get_channels().begin(); chan != serv.get_channels().end(); chan++)
			{
				if ((*target) == (*chan).str_name())
				{
					(*chan).send_message(serv, u, message);
				}
			}
			return (0);
		}
		else
		{
			occ_e = (*target).find("!");
			occ_a = (*target).find("@");
			occ_p = (*target).find("%");

			if (occ_e != (unsigned long)(-1) && occ_e < occ_a && occ_e < occ_p)
			{
				nick = (*target).substr(0, occ_e);
				recipient = serv.getuserbynick(nick);
			}
			else if (occ_a != (unsigned long)(-1) && occ_a < occ_e && occ_a < occ_p)
			{
				nick = (*target).substr(0, occ_a);
				recipient = serv.getuserbynick(nick);
			}
			else if (occ_p != (unsigned long)(-1) && occ_p < occ_e && occ_p < occ_a)
			{
				nick = (*target).substr(0, occ_p);
				recipient = serv.getuserbynick(nick);
			}
			else
				recipient = serv.getuserbynick((*target));
			
			if (recipient == NULL)
			{
				send_reply(CODE_ERR_NOSUCHNICK, serv, u, message);
				return (-3);
			}
			else
			{
				rep = ":" + u.get_nickname() + "!" + u.get_username() + "@" + u.get_hostname() + " " +\
				message[0] + " " + (*target) + " " + (message[2]) + "\r\n";
				//serv.write_socket(u.get_fd(), rep);
				std::cerr << MAG << ":recipient: " << recipient->get_nickname() << ENDL;
				i = serv.write_socket(recipient->get_fd(), rep);
				std::cerr << recipient->get_nickname() << " > " + rep;
				if (recipient->get_modes().get_a())
				{
					std::vector<std::string> tmp(2);
					tmp[0] = recipient->get_nickname();
					tmp[1] = recipient->get_awaymsg();
					std::cerr << MAG << "Awaymsg:" << recipient->get_awaymsg() << ENDL;
					std::cerr << MAG << "Awaymsg:" << tmp[1] << ENDL;
					send_reply(CODE_RPL_AWAY, serv, u, message, tmp);
				}
				return (i);
			}
		}
	}
	return (-2);
}

int PART(Server &serv, User &u, std::vector<std::string> message)
{
	std::vector<std::string> channels;
	std::vector<std::string>::iterator begin, end;
	std::list<Channel>::iterator c_begin, c_end;
	int i;

	if (message.size() < 2)
	{
		send_reply(CODE_ERR_NEEDMOREPARAMS, serv, u, message);
		return (1);
	}
	
	channels = split_on(message[1], ',');
	end = channels.end();
	for (begin = channels.begin(); begin != end; begin++)
	{
		for (c_begin = serv.get_channels().begin(); c_begin != serv.get_channels().end(); c_begin++)
		{
			if ((*c_begin).str_name() == *begin)
			{
				//PART
				i = (*c_begin).get_users().size();
				if ((*c_begin).remove_user(&u) == i)
				{
					send_reply(CODE_ERR_NOTONCHANNEL, serv, u, message, std::vector<std::string>(1, *begin));
					break ;
				}

				u.remove_channel(&(*c_begin));
				break ;
			}
		}
		if (c_begin == serv.get_channels().end())
		{
			send_reply(CODE_ERR_NOSUCHCHANNEL, serv, u, message, std::vector<std::string>(1, *begin));
		}
	}
	return (0);
}

int PING(Server &serv, User &u, std::vector<std::string> message)
{
	return (PONG(serv, u, message));
}

int PONG(Server &serv, User &u, std::vector<std::string> message)
{
	std::string rep = "PONG";
	size_t i = 1;
	int ret;

	while (i < message.size())
	{
		rep += " " + message[i++];
	}
	rep += "\r\n";
	
	std::cout << u.get_nickname() << " > " << rep;
	ret = serv.write_socket(u.get_fd(), rep);

	return (ret);
}

int QUIT(Server &serv, User &u, std::vector<std::string> message)
{
	//Nothing to reply ?
	
	serv.disconnect_user(u);
	(void)message;
	return (0);
}

int USER(Server &serv, User &u, std::vector<std::string> message)
{
	if (message.size() != 5)
	{
		send_reply(CODE_ERR_NEEDMOREPARAMS, serv, u, message);
		return (1);
	}
	else if (u.get_username() != "")
	{
		send_reply(CODE_ERR_ALREADYREGISTRED, serv, u, message);
		return (2);
	}

	u.set_username(message[1]);
	u.set_modes(message[2][0] - '0');
	// message[3] UNUSED
	u.set_realname(message[4]);
	u.set_hostname("ft.placeholder.net"); // TODO understand the hostname
	if (u.get_nickname() != "")
		greeting(serv, u, message);

	return (0);
}

int WHOIS(Server &serv, User &u, std::vector<std::string> message)
{
	User *nick;
	std::vector<std::string> data(10);
	if (message.size() == 1)
	{
		send_reply(CODE_ERR_NONICKNAMEGIVEN, serv, u, message);
		return (-1);
	}
	//target: TODO later when Server-to-Server is done
	nick = serv.getuserbynick(message[1]);
	if (nick == NULL || nick->get_modes().get_i() == true)
	{
		send_reply(CODE_ERR_NOSUCHNICK, serv, u, message);
		return (-2);
	}
	data[0] = nick->get_nickname();
	data[1] = nick->get_username();
	//data[2] = nick->get_hostname();
	data[2] = "ft.placeholder.net";
	data[3] = nick->get_realname();
	//data[4] = nick->get_idletime(); // TODO get idle time
	data[4] = "0";
	send_reply(CODE_RPL_WHOISUSER, serv, u, message, data);
	send_reply(CODE_RPL_WHOISSERVER, serv, u, message);
	if (nick->get_modes().get_o())
		send_reply(CODE_RPL_WHOISOPERATOR, serv, u, message, data);
	send_reply(CODE_RPL_WHOISIDLE, serv, u, message, data);

	//send_reply(CODE_RPL_WHOISCHANNELS, serv, u, message, other); // TODO: WHOISCHANNELS (cf:https://modern.ircdocs.horse/)

	send_reply(CODE_RPL_ENDOFWHOIS, serv, u, message, data);
	return (0);
}

int OPER(Server &serv, User &u, std::vector<std::string> message)
{
	if (message.size() < 3)
	{
		send_reply(CODE_ERR_NEEDMOREPARAMS, serv, u, message);
		return (1);
	}
	if (message[2] != serv.get_password())
	{
		send_reply(CODE_ERR_PASSWDMISMATCH, serv, u, message);
		return (1);
	}
	// TODO If user is not in the list of Users allowed to be op by the server. You need to return ERR_NOOPERHOST.
	std::list<User>::iterator it = serv.get_users().begin();
	while (it != serv.get_users().end())
	{
		if (it->get_nickname() == message[1])
		{
			it->get_modes().set_o();
			send_reply(CODE_RPL_YOUREOPER, serv, u, message);
			return (0);
		}
		it++;
	}
	return (0);
}

int PASS(Server &serv, User &u, std::vector<std::string> message)
{
	if (message.size() < 2)
	{
		send_reply(CODE_ERR_NEEDMOREPARAMS, serv, u, message);
		return (1);
	}
	// TODO Rajouter: Impossible de le changer une fois le serveur connecter. Err: ERR_ALREADYREGISTRED
	/*
	if (serv.get_password() != NULL)
	{
		send_reply(CODE_ERR_ALREADYREGISTRED, serv, u, message);
		return (1);
	}*/
	serv.set_password(message[1]);
	return (0);
}

int ISON(Server &serv, User &u, std::vector<std::string> message)
{
	std::vector<std::string> list_nickname;
	list_nickname.push_back("");

	if (message.size() < 2)
	{
		send_reply(CODE_ERR_NEEDMOREPARAMS, serv, u, message);
		return (1);
	}
	std::vector<std::string>::iterator it = message.begin();
	it++;
	while (it != message.end())
	{
		std::list<User>::iterator it2 = serv.get_users().begin();
		while (it2 != serv.get_users().end())
		{
			if (*it == it2->get_nickname())
			{
				list_nickname[0] += *it + " ";
			}
			it2++;
		}
		it++;
	}
	send_reply(CODE_RPL_ISON, serv, u, message, list_nickname);
	return (0);
}