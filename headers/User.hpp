/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:30:24 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/22 13:36:28 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include "Utils.hpp"
#include "UModes.hpp"
#include "Channel.hpp"

class Channel;

class User
{
	private:
		int _fd;
		bool _real_user;
		std::string _nickname;
		std::string _username;
		std::string _hostname;
		std::string _realname;
		UModes _modes;
		std::string _awaymsg;
		std::list<Channel*> _channels;
	
	public:
		User();
		User(int const &fd, std::string const & nick = "", std::string const & name = "");
		User(User const &u);

		User &operator=(User const &u);
		bool operator==(User const &u) const;
		bool operator!=(User const &u) const;

		int get_fd() const;
		std::string get_nickname() const;
		std::string get_username() const;
		std::string get_hostname() const;
		std::string get_realname() const;
		UModes &get_modes();
		std::string get_awaymsg() const;
		int get_nb_channels() const;
		bool get_real_user() const;

		void set_fd(int const &fd);
		void set_nickname(std::string const &nick);
		void set_username(std::string const &name);
		void set_hostname(std::string const &host);
		void set_realname(std::string const &real);
		void set_modes(int i);
		void set_awaymsg(std::string const &msg);
		void set_real_user(bool i);

		bool matches_mask(std::string mask) const;
		int add_channel(Channel *u);
		int remove_channel(Channel *u);

		std::string full_id() const;
};

#endif