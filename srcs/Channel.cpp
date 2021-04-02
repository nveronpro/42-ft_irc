/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:31:14 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/24 15:30:12 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"

Channel::Channel()
{
	this->_prefix = '#';
	this->_name = "(null)";
	this->_topic = "(null)";
	this->_size = -1;
}

Channel::Channel(Channel const &c)
{
	(*this) = c;
}

Channel &Channel::operator=(Channel const &c)
{
	this->_prefix = c._prefix;
	this->_name = c._name;
	this->_users = c._users;
	this->_modes = c._modes;
	this->_topic = c._topic;
	this->_password = c._password;
	this->_size = c._size;
	this->_banned = c._banned;
	return (*this);
}

Channel::Channel(char prefix, std::string name, std::string topic, int size)
{
	if (prefix != '#' && prefix != '!' && prefix != '&' && prefix != '+')
	{
		std::string str = "Received prefix: ";
		str += prefix;
		str += ". Expected: [#|!|&|+]";

		throw (std::invalid_argument(str));
	}
	if (name == "")
	{
		std::string str = "Received name: \"\"";
		str += ". Expected: a name?";

		throw (std::invalid_argument(str));
	}
	this->_prefix = prefix;
	this->_name = name;
	this->_topic = topic;
	this->_size = size;
	if (size > -1)
		this->_modes.set_l(true);
}

Channel::Channel(std::string full_name, std::string password)
{
	this->_prefix = full_name[0];
	this->_name = full_name.substr(1);
	this->_password = password;
	this->_size = -1;
	if (password != "")
		this->_modes.set_k(true);
}

bool Channel::operator==(Channel const &c)
{
	return (this->_prefix == c._prefix && this->_name == this->_name);
}
bool Channel::operator!=(Channel const &c)
{
	return (!((*this) == c));
}

char Channel::get_prefix() const {return (this->_prefix);}
std::string Channel::get_name() const {return (this->_name);}
std::list<User*> &Channel::get_users() {return (this->_users);}
std::string Channel::get_topic() const {return (this->_topic);}
CModes &Channel::get_modes() {return (this->_modes);}

void Channel::set_topic(std::string const str)
{
	this->_topic = str;
}

int Channel::add_user(User *u)
{
	this->_users.push_back(u);
	return (this->_users.size());
}


int Channel::remove_user(User *u)
{
	std::list<User*>::iterator begin, end;
	begin = this->_users.begin();
	end = this->_users.end();
	while (begin != end && *begin != u)
		begin++;
	if (begin != end)
	{
		this->_users.erase(begin);
	}
	
	return (this->_users.size());
}

bool Channel::has_user(User *u)
{
	std::list<User*>::iterator begin, end;

	begin = this->_users.begin();
	end = this->_users.end();

	while (begin != end)
	{
		if (*(*begin) == *u)
			return (true);
		begin++;
	}
	return (false);
}
/*
int Channel::send_message(Server const &s, std::string const &to_send)
{
	std::list<User*>::iterator begin, end;

	begin = this->_users.begin();
	end = this->_users.end();

	while (begin != end)
	{
		s.write_socket((*begin)->get_fd(), to_send);
		begin++;
	}
	return (0);
}*/

bool Channel::is_user_banned(User const &u)
{
	std::list<std::string>::iterator begin, end;

	begin = this->_banned.begin();
	end = this->_banned.end();

	while (begin != end)
	{
		if (u.matches_mask(*begin))
			return (true);
		begin++;
	}
	return (false);
}

void Channel::ban_mask(std::string str)
{
	this->_banned.push_back(str);
}

std::string Channel::str_name() const
{
	std::string res = "!";

	res[0] = this->_prefix;
	res += this->_name;

	return (res);
}

void Channel::send_message(Server &serv, User &u, std::vector<std::string> message) const
{
	std::string rep = "";
	rep = ":" + u.get_nickname() + "!" + u.get_username() + "@" + u.get_hostname() + " " +\
			message[0] + " " + this->_prefix + this->_name + " " + (message[2]) + "\r\n";

	for (std::list<User*>::const_iterator user = this->_users.begin(); user != this->_users.end(); user++)
	{
		if (u.full_id() != (*user)->full_id())
		{
			std::cerr << (*user)->get_nickname() << " > " + rep;
			serv.write_socket((*user)->get_fd(), rep);
		}
	}
}

void Channel::send(Server &serv, std::string message)
{
	for (std::list<User*>::const_iterator user = this->_users.begin(); user != this->_users.end(); user++)
	{
		std::cerr << (*user)->get_nickname() << " > " + message;
		serv.write_socket((*user)->get_fd(), message);
	}
}


