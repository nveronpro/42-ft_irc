/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:10:23 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/24 15:48:10 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/replies.hpp"

#include <sstream>
std::string itos(int const i)
{
	std::stringstream ss;
	std::string s;
	
	ss << i;
	ss >> s;

	return (s);
}

int send_reply(int code, Server &s, User &u, std::vector<std::string> const &message, std::vector<std::string> const &other)
{
	std::string rep;
	int i;

	std::cout << RED << message[0] << ENDL;
	rep = build_reply(code, s, u, message, other);
	i = s.write_socket(u.get_fd(), rep);
	std::cerr << u.get_nickname() << " > " + rep;
	return (i);
}

std::string build_reply(int code, Server &s, User &u, std::vector<std::string> const &message, std::vector<std::string> const &other)
{
	std::string res = "";

	res += ":127.0.0.1 ";
	if (code < 10)
		res += "00";
	else if (code < 100)
		res += "0";
	res += itos(code) + " ";
	if (u.get_nickname() == "")
		res += "* ";
	else
		res += u.get_nickname() + " ";

	if (code == CODE_RPL_WELCOME)	//001
		res += INIT_RPL_WELCOME(u.get_nickname(), u.get_username(), u.get_hostname());
	else if (code == CODE_RPL_YOURHOST) //002
		res += INIT_RPL_YOURHOST("PLACEHOLDER", SERVER_VER);
	//else if (code == CODE_RPL_CREATED) //003
	//	res += INIT_RPL_CREATED("TODAY");
	else if (code == CODE_RPL_MYINFO) //004
		res += INIT_RPL_MYINFO("PLACEHOLDER", SERVER_VER, "NO_UMODES", "NO_CMODES");

	else if (code == CODE_RPL_LUSERCLIENT) // 251
		res += INIT_RPL_LUSERCLIENT(s.get_users().size(), 0, 0); //TODO: change services and server number
	else if (code == CODE_RPL_LUSEROP) // 252
		res += INIT_RPL_LUSEROP(0 /*TODO: get number of OP users*/);
	else if (code == CODE_RPL_LUSERUNKNOWN) // 253
		res += INIT_RPL_LUSERUNKNOWN(0/*TODO: get number of unknown(?) users*/);
	else if (code == CODE_RPL_LUSERCHANNELS) // 254
		res += INIT_RPL_LUSERCHANNELS(0/*TODO: get number of channels*/);
	else if (code == CODE_RPL_LUSERME) // 255
		res += INIT_RPL_LUSERME(s.get_users().size(), 0/* TODO: get number of servers in network */);


	else if (code == CODE_RPL_AWAY) // 301
		res += INIT_RPL_AWAY(other.at(0), other.at(1));
	else if (code == CODE_RPL_UNAWAY) // 305
		res += INIT_RPL_UNAWAY;
	else if (code == CODE_RPL_NOWAWAY) // 306
		res += INIT_RPL_NOWAWAY;
	
	else if (code == CODE_RPL_WHOISUSER) // 311
		res += INIT_RPL_WHOISUSER(other[0], other[1], other[2], other[3]);
	else if (code == CODE_RPL_WHOISSERVER) // 312
		res += INIT_RPL_WHOISSERVER(u.get_nickname(), s.get_name(), "SERVER INFO TODO");
	else if (code == CODE_RPL_WHOISOPERATOR) // 313
		res += INIT_RPL_WHOISOPERATOR(other[0]);
	else if (code == CODE_RPL_WHOISIDLE) // 317
		res += INIT_RPL_WHOISIDLE(other[0], other[4]);
	else if (code == CODE_RPL_ENDOFWHOIS) // 318
		res += INIT_RPL_ENDOFWHOIS(u.get_nickname());
	else if (code == CODE_RPL_WHOISCHANNELS)  // 319
		res += INIT_RPL_WHOISCHANNELS(u.get_nickname(), "TODO: Channels&perms");
	
	else if (code == CODE_RPL_TOPIC) //332
		res += INIT_RPL_TOPIC(other[0], other[1]);
		
	else if (code == CODE_RPL_NAMREPLY) // 353
		res += INIT_RPL_NAMREPLY(other[0], other[1]);

	else if (code == CODE_RPL_ENDOFNAMES) // 366
		res += INIT_RPL_ENDOFNAMES(other[0]);

	else if (code == CODE_RPL_MOTD) // 372
		res += INIT_RPL_MOTD(s.get_name());
	else if (code == CODE_RPL_MOTDSTART) // 375
		res += INIT_RPL_MOTDSTART(s.get_motd());
	else if (code == CODE_RPL_ENDOFMOTD) // 376
		res += INIT_RPL_ENDOFMOTD;
	else if (code == CODE_RPL_YOUREOPER) // 381
		res += INIT_RPL_YOUREOPER(s.get_name() ,u.get_nickname());
	else if (code == CODE_RPL_ISON) //303
		res += INIT_RPL_ISON(other[0]);

	else if (code == CODE_ERR_NOSUCHNICK) // 401
		res += INIT_ERR_NOSUCHNICK(message[1]);
	else if (code == CODE_ERR_NOSUCHCHANNEL) // 403
		res += INIT_ERR_NOSUCHCHANNEL(other[0]);
	else if (code == CODE_ERR_TOOMANYCHANNELS) // 405
		res += INIT_ERR_TOOMANYCHANNELS(other[0]);
	else if (code == CODE_ERR_UNKNOWNCOMMAND) // 422
		res += INIT_ERR_UNKNOWNCOMMAND(message[0]);
	else if (code == CODE_ERR_NOMOTD) // 422
		res += INIT_ERR_NOMOTD;
	else if (code == CODE_ERR_NONICKNAMEGIVEN) // 431
		res+= INIT_ERR_NONICKNAMEGIVEN;
	else if (code == CODE_ERR_NICKNAMEINUSE) // 433
		res += INIT_ERR_NICKNAMEINUSE(message[1]);
	else if (code == CODE_ERR_UNAVAILRESOURCE) // 437
		res += INIT_ERR_UNAVAILRESOURCE(other[0]);
	else if (code == CODE_ERR_NOTONCHANNEL) // 442
		res += INIT_ERR_NOTONCHANNEL(other[1]);
	else if (code == CODE_ERR_NOTREGISTERED) // 451
		res += INIT_ERR_NOTREGISTERED;
	else if (code == CODE_ERR_NEEDMOREPARAMS) // 461
		res += INIT_ERR_NEEDMOREPARAMS(message[0]);
	else if (code == CODE_ERR_ALREADYREGISTRED) // 462
		res += INIT_ERR_ALREADYREGISTRED;
	else if (code == CODE_ERR_CHANNELISFULL) // 471
		res += INIT_ERR_CHANNELISFULL(other[0]);
	else if (code == CODE_ERR_INVITEONLYCHAN) // 473
		res+= INIT_ERR_INVITEONLYCHAN(other[0]);
	else if (code == CODE_ERR_BANNEDFROMCHAN) // 474
		res += INIT_ERR_BANNEDFROMCHAN(other[0]);
	else if (code == CODE_ERR_BADCHANNELKEY) // 475
		res += INIT_ERR_BADCHANNELKEY(other[0]);
	else if (code == CODE_ERR_BADCHANMASK) // 476
		res += INIT_ERR_BADCHANMASK(other[0]);
	else if (code == CODE_ERR_PASSWDMISMATCH) // 464
		res += INIT_ERR_PASSWDMISMATCH;


	else
	{
		std::cout << RED << "Whoops ! You tried to use a code that is not defined !\n";
		std::cerr << "Code used: " << code << ENDL;
	}
	
	res += "\r\n";
	(void)s;
	return (res);
}