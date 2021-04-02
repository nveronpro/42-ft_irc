/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:00:14 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/23 17:37:49 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/User.hpp"

User::User()
{
	this->_fd = -1;
	this->_nickname = "";
	this->_username = "";
}

User::User(int const &fd, std::string const & nick, std::string const & name)\
	: _fd(fd), _nickname(nick), _username(name)
{
	return;
}

User::User(User const &u)
{
	(*this) = u;
}

User &User::operator=(User const &u)
{
	this->_fd = u._fd;
	this->_nickname = u._nickname;
	this->_username = u._username;

	return (*this);
}

bool User::operator==(User const &u) const
{
	return (
		this->_fd == u._fd &&
		this->_nickname == u._nickname &&
		this->_username == u._username &&
		this->_hostname == u._hostname &&
		this->_realname == u._realname
	);
}

bool User::operator!=(User const &u) const
{
	return (!((*this) == u));
}

int User::get_fd() const {return (this->_fd);}
std::string User::get_nickname() const {return (this->_nickname);}
std::string User::get_username() const {return (this->_username);}
std::string User::get_hostname() const {return (this->_hostname);}
std::string User::get_realname() const {return (this->_realname);}
UModes &User::get_modes() {return (this->_modes);}
std::string User::get_awaymsg() const {return (this->_awaymsg);}
int User::get_nb_channels() const {return (this->_channels.size());}
bool User::get_real_user() const {return (this->_real_user);};


void User::set_fd(int const &fd) {this->_fd = fd;}
void User::set_nickname(std::string const &nick) {this->_nickname = nick;}
void User::set_username(std::string const &name) {this->_username = name;}
void User::set_hostname(std::string const &host) {this->_hostname = host;}
void User::set_realname(std::string const &real) {this->_realname = real;}
void User::set_modes(int i) {this->_modes.set(i);}
void User::set_awaymsg(std::string const &msg) {this->_awaymsg = msg;}
void User::set_real_user(bool i){ this->_real_user = i;}

/*
**	str is an expression
**	match is the mask part: May contain wildcards
*/
bool matches_expression(std::string str, std::string match) 
{
	int str_i;
	int match_i;
	
	if (match == "*")
		return (true);
	
	match_i = 0;
	str_i = 0;
	while (match[match_i])
	{
		if (match[match_i] == '?')
		{
			//any char EXCEPT EoS
			if (str[str_i] == '\0')
				return (false);
			match_i++;
			str_i++;
		}
		else if (match[match_i] == '*')
		{
			//if wild car is an empty string
			if (matches_expression(str.substr(str_i), match.substr(match_i + 1)))
				return (true);
			//otherwise test every possibility
			if (str[str_i] == '\0' && matches_expression(str.substr(str_i + 1), match.substr(match_i)))
				return (true);
			//no possibility found so it is false
			return (false);
		}
		else
		{
			//normal caseless comparison
			if (std::tolower(str[str_i]) != std::tolower(match[match_i]))
				return (false);
			match_i++;
			str_i++;
		}
	}
	return (str[str_i] == '\0' && match[match_i] == '\0');

}

bool User::matches_mask(std::string mask) const
{
	std::string nick, user, host;
	int i = 0;
	int first = 0;

	while (mask[i] != '!')
		i++;
	nick = mask.substr(first, i);

	++i;
	first = i;
	while (mask[i] != '@')
		i++;
	user = mask.substr(first, i);

	++i;
	first = i;
	while (mask[i] != '\0')
		i++;
	host = mask.substr(first, i);

	return (matches_expression(this->_nickname, nick) &&
			matches_expression(this->_username, user) &&
			matches_expression(this->_hostname, host));
}

int User::add_channel(Channel *u)
{
	if (this->_channels.size() <= MAX_CHANNELS)
		this->_channels.push_back(u);
	else
	{
		throw (std::length_error("Error:User has already reached the channel limit"));
	}
	return (this->_channels.size());
	
}

int User::remove_channel(Channel *u)
{
	std::list<Channel*>::iterator begin, end;


	begin = this->_channels.begin();
	end = this->_channels.end();
	while (begin != end && (*begin) != u)
	{
		begin++;
	}
	if (begin == end)
	{
		throw (std::invalid_argument("Error: trying to remove a channel that does not exist\n"));
	}
	this->_channels.erase(begin);
	return (this->_channels.size());
}

std::string User::full_id() const
{
	std::string res = this->_nickname + "!" + this->_username + "@" + this->_hostname;

	return (res);
}


