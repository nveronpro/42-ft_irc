/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:14:27 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/24 15:30:06 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "User.hpp"
# include "Server.hpp"
# include "CModes.hpp"

class User;

class Channel
{
	private:
		/*
		**	&: Local channel, on ly on this server
		**	+: Do not support channel modes
		**	!: Creator marked as CHannel OPerator (chop)
		**	#: other ? normal channel ?
		*/
		char _prefix;
		std::string _name;
		std::list<User*> _users;
		CModes _modes;
		std::string _topic;
		std::string _password;
		
		int _size;
		std::list<std::string> _banned;

	public:

		Channel();
		Channel(Channel const &c);

		Channel(char prefix, std::string name, std::string topic = "", int size = -1);
		Channel(std::string full_name, std::string password = "");

		Channel &operator=(Channel const &c);

		bool operator==(Channel const &c);
		bool operator!=(Channel const &c);
		char get_prefix() const;
		std::string get_name() const;
		std::list<User*> &get_users();
		std::string get_topic() const;
		CModes &get_modes();

		//you can not change a channel's name
		//you can not change a channel's user list
		void set_topic(std::string const str = "");

		int add_user(User *u);
		int remove_user(User *u);
		bool has_user(User *u);
		/*int send_message(Server const &s, std::string const &to_send);*/
		bool is_user_banned(User const &u);
		void ban_mask(std::string str);
		std::string str_name() const;
		void send_message(Server &serv, User &u, std::vector<std::string> message) const;
		void send(Server &serv, std::string message);
};

#endif