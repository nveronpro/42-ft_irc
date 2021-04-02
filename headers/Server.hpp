/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:29:24 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/22 14:26:10 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class Server;

# include "User.hpp"
# include "replies.hpp"
# include "commands.hpp"
# include "Channel.hpp"
# include "OtherServer.hpp"

# define SERVER_VER "0.3"

class Server
{
	private:
		int _status;
		std::string _name;

		int _port;
		std::string _password;

		std::string _hostname;
		int	_hostport;
		std::string _hostpassword;
		int _hostsocket;

		int _serverfd;

		std::list<User> _users;
		fd_set 	_sockets;
		std::string _motd;

		std::list<Channel> _channels;

		//Private coplian methods
		Server(Server const &s);
		Server &operator=(Server const & s);

	public:
		//CONSTRUCTORS
		Server();
		Server(int port, std::string password, std::string name = "");
		Server(int port, std::string password, std::string hostname, int hostport, std::string _hostpassword, std::string name = "");


		//GETTERS
		int get_status() const;
		std::string get_name() const;
		int get_port() const;
		std::string get_password() const;
		std::string get_hostname() const;
		int get_hostport() const;
		int get_hostsocket() const;
		std::string get_hostpassword() const;
		int get_serverfd() const;
		std::list<User> &get_users();
		std::string get_motd() const;
		std::list<Channel> &get_channels();
		
		//SETTERS
			//status can not be modified
		void set_name(std::string const pass);
		void set_port(int p);
		void set_password(std::string const pass);
		void set_hostname(std::string const host);
		void set_hostport(int const port);
		void set_hostsocket(int const socket);
		void set_hostpassword(std::string hostpass);
		void set_motd(std::string motd);
			//serverfd can not be modified

		//init_server()
		int create_socket();
		int set_socket();
		int bind_socket();
		int listen_socket();

		/*
		**	Create the socket, set it, bind it, listen.
		**	return value: 
		**		0 if ok
		**		other if error
		*/
		int init_server();

		int start_server();

		/*
		**	reset_sockets:
		**	resets the fd_set with all the users
		*/
		void reset_sockets();
		
		/*
		**	accept_connection:
		**	reads the _serverfd to accept incoming connection
		*/
		int accept_connection();

		/*	message_splitter:
		**		char *buffer: the received data from the user
		**		vector<string> &message: the separated string ready to be checked
		**	will split the received data into multiple string for easy parsing
		*/
		int message_splitter(char *&buffer, std::vector<std::string> &message);

		int read_socket(User &u);

		int write_socket(int const fd, std::string const &message) const;

		/*
		**	receive data:
		**	will check all sockets. the first one found with
		**	data will be read and sent to message_parser()
		*/
		int receive_data();

		/*
		**	check_connection:
		**	
		*/
		int check_connection();

		/*
		**	getuserbynick:
		**		return nullptr if not found
		**		address to the user if found
		**	Check the existence of a user using nick
		*/
		User *getuserbynick(std::string const nick);

		/*
		**	getuserbyfd:
		**		return NULL if not found
		**		address to the user if found
		**	Check the existence of a user using fd
		*/
		User *getuserbyfd(int fd);

		int disconnect_user(std::list<User>::iterator const &it);
		int disconnect_user(User const &u);

		std::list<Channel>::iterator add_channel(std::string name, std::string password);
		int delete_channel(std::string name);
		std::list<Channel>::iterator has_channel(std::string full_name);

		/*
		**	find channel using prefix & name
		**	returns:
		**	list.end() if not found
		**	iterator to the channel otherwise
		**/
		std::list<Channel>::iterator find_channel(char prefix, std::string name);
};

#endif
