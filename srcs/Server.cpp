/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:10:39 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/22 17:22:10 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

//Private coplian methods
Server::Server(Server const &s)
{
	(*this) = s;
}

Server &Server::operator=(Server const & s)
{
	this->_status = 0;
	this->_port = s._port;
	this->_name = s._name;
	this->_password = s._password;
	this->_hostname = s._hostname;
	this->_hostport = s._hostport;
	this->_hostpassword = s._hostpassword;
	this->_serverfd = s._serverfd;
	this->_users = s._users;
	this->_sockets = s._sockets;

	return (*this);
}


//FUNCTIONS


Server::Server()
{
	this->_status = 0;
	this->_port = 0;
	this->_name = "";
	this->_password = "";
	this->_hostname = "";
	this->_hostport = 0;
	this->_hostpassword = "";
	this->_serverfd = -1;
	this->_users = std::list<User>();
}

Server::Server(int port, std::string password, std::string name)
{
	this->_status = 0;
	this->_port = port;
	this->_name = name;
	this->_password = password;
	this->_hostname = "";
	this->_hostport = 0;
	this->_hostpassword = "";
	this->_serverfd = -1;
	this->_users = std::list<User>();
}

Server::Server(int port, std::string password, std::string hostname, int hostport, std::string _hostpassword, std::string name)\
	: _status(0), _name(name), _port(port), _password(password), _hostname(hostname), _hostport(hostport), _hostpassword(_hostpassword), _serverfd(-1)
{
	this->_users = std::list<User>();
	return ;
}

//GETTERS
int Server::get_status() const {return (this->_status);}
std::string Server::get_name() const {return (this->_name);}
int Server::get_port() const {return (this->_port);}
std::string Server::get_password() const {return (this->_password);}
std::string Server::get_hostname() const {return (this->_hostname);}
int Server::get_hostport() const {return (this->_hostport);}
int Server::get_hostsocket() const {return (this->_hostsocket);}
std::string Server::get_hostpassword() const {return (this->_hostpassword);}
int Server::get_serverfd() const {return (this->_serverfd);}
std::list<User> &Server::get_users() {return (this->_users);}
std::string Server::get_motd() const {return (this->_motd);}
std::list<Channel> &Server::get_channels() {return (this->_channels);};

void Server::set_name(std::string const name) {this->_name = name;}
//can't set status
void Server::set_port(int p) {this->_port = p;}
void Server::set_password(std::string const pass) {this->_password = pass;}
void Server::set_hostname(std::string const host) {this->_hostname = host;}
void Server::set_hostport(int const port) {this->_hostport = port;}
void Server::set_hostsocket(int const socket) {this->_hostsocket = socket;}
void Server::set_hostpassword(std::string hostpass) {this->_hostpassword = hostpass;}
void Server::set_motd(std::string motd) {this->_motd = motd;}
//can't set serverfd


//init_server()
int Server::create_socket()
{
	//AF_INET6: set socket as ipv6
	//SOCK_STREAM: create an in/out data stream
	if ((this->_serverfd = socket(AF_INET6, SOCK_STREAM, 0)) == 0) 
	{ 
		this->_status = -1;
		std::cerr << RED << "Error:\n Socket creation failed with code " << errno << ENDL;
		perror("socket failed"); 
		return (1); 
	}
	else
	{
		this->_status = 1;
		return (0);
	}
}

int Server::set_socket()
{
	int opt;

	opt = 1;
	// saying that the port shall be reused
	//SOL_SOCKET: Specify the layer of the socket
	//SO_REUSEADDR: Allow port duplication, for multiple procersses to use the port
	//SO_REUSEPORT: aLLOWS   FULL DUPLICATE (KINDA SIMILAR ?)
	if (setsockopt(this->_serverfd, SOL_SOCKET, SO_REUSEADDR/* | SO_REUSEPORT*/, 
												  &opt, sizeof(opt))) 
	{
		this->_status = -1;
		std::cerr << RED << "Error:\nsetsockopt failed with code " << errno << ENDL;
		perror("setsockopt(SOL_SOCKET)");
		return (1);
	}
	opt = 0;
	//IPV6_V6ONLY=0: allowing both ipv6 AND ipv4 on the port
	if (setsockopt(this->_serverfd, IPPROTO_IPV6, IPV6_V6ONLY, &opt, sizeof(opt)))
	{
		this->_status = -2;
		std::cerr << RED << "Error:\nsetsockopt failed with code " << errno << ENDL;
		perror("setsockopt(IPPROTO_IPV6)");
		return (1);
	}
	this->_status = 2;
	return (0);
}

/*
**	sockaddr_in6 parameters;
**		sin6_family: Always AF_INET6
**		sin6_port: The port to listen to
**		sin6_flowinf: "the IPv6 flow identifier"
**		sin6_addr: The ipv6 IP address
**		sin6_scope_id: "ID depending on the scope of the address"
*/
int Server::bind_socket()
{
	struct sockaddr_in6 address;
	int addrlen = sizeof(address);
	
	address.sin6_family = AF_INET6; 
	address.sin6_port = htons(this->_port); 
	address.sin6_flowinfo = 0;
	address.sin6_addr = in6addr_any;
	address.sin6_scope_id = 0;

	// Attaching socket to the port 8080 
	//"naming the socket"
	if (bind(this->_serverfd, (struct sockaddr *)(&address), addrlen) <0) 
	{
		this->_status = -3;
		std::cerr << RED << "Error:\nbind failed with code " << errno << ENDL;
		perror("bind failed"); 
		return (1); 
	}
	this->_status = 3;
	return (0);
}

int Server::listen_socket()
{
	if (listen(this->_serverfd, 3) < 0)
	{
		this->_status = -4;
		std::cerr << RED << "Error:\nlisten failed with code " << errno << ENDL;
		perror("listen");
		return (1);
	}
	this->_status = 4;
	return (0);
}

int Server::init_server()
{
	if (this->create_socket())
	{
		return (1);
	}
	if (this->set_socket())
	{
		return (2);
	}
	if (this->bind_socket())
	{
		return (3);
	}
	if (this->listen_socket())
	{
		return (4);
	}
	return (0);
}

int Server::start_server()
{
	int i;
	timeval timeout;
	//int valread;
	////char buffer[1024] = {0};


	if (this->_status != 4)
	{
		std::cerr << RED << "Error:\nServer is not ready to launch\
(run init_server() and/or check server status)" << ENDL;
	}
	else
	{
		this->_status = 5;
		while (this->_status == 5)
		{
			this->reset_sockets();
			timeout.tv_usec = 0;	//placeholders
			timeout.tv_sec = 10;	//placeholders
			//std::cerr << CYAN << "\nwaiting for data..." << ENDL;
			i = select(FD_SETSIZE, &(this->_sockets), NULL, NULL, &timeout);
			if (i > 0)
			{
				if (FD_ISSET(this->_serverfd, &(this->_sockets)))
				{
					this->accept_connection();
					CGREEN << "Connection accepted !" << ENDL;
					i--;
				}
				if (i > 0)
				{
					//CMAG << "data received !" << ENDL;
					this->receive_data();
				}
			}
			/*while ((valread = read( this->get_hostsocket() , buffer, 1024)) > 0)
			{
				std::cout << buffer << std::endl;
			}*/
			//std::cerr << GREY << "checking connections..." << ENDL;
			//this->check_connection();
			//std::cerr << GREY << "connections checked" << ENDL;
		}
	}
	return (0); //placeholder
}

void Server::reset_sockets()
{
	std::list<User>::iterator it, end;

	FD_ZERO(&(this->_sockets));
	FD_SET(this->_serverfd, &(this->_sockets));
	it = this->_users.begin();
	end = this->_users.end();
	while (it != end)
	{
		FD_SET((*it).get_fd(), &(this->_sockets));
		it++;
	}
}

int Server::accept_connection()
{
	int new_socket;
	struct sockaddr_in6 address;
	int addrlen = sizeof(address);
	char buffer[513];
	std::vector<std::string> message;
	User new_user;

	bzero(buffer, 513);

//std::string tmp_rep = "";
	
	address.sin6_family = AF_INET6; 
	address.sin6_port = htons(this->_port); 
	address.sin6_flowinfo = 0;
	address.sin6_addr = in6addr_any;
	address.sin6_scope_id = 0;
	
	new_socket = accept(this->_serverfd, (struct sockaddr *)(&address), (socklen_t*)&addrlen);
	if (new_socket < 0) 
	{
		perror("accept");
		printf("errno:%d\n", errno);
		return (1);
	}
	else
	{
		CGREEN << "Connection Established !" << ENDL;

		fcntl(new_socket, F_SETFL, O_NONBLOCK);
		new_user = User(new_socket);
		this->_users.push_back(new_user);
		std::cerr << "nb_user: " << this->_users.size() << "\n";

		
		return (0);
	}
}

int Server::read_socket(User &u)
{
	int read;
	char buffer[513];
	char *ptr_buffer = buffer;
	std::vector<std::string> message;

	bzero(buffer, 513);
	read = recv(u.get_fd(), ptr_buffer, 512, 0);
	std::cout << "Message received ! read " << read << " characters !\n";
	if (read > 0)
	{
		while (*ptr_buffer != 0)
		{
			std::cerr << GREY << "buffer:" << buffer << ENDL;
			message.clear();
			this->message_splitter(ptr_buffer, message);
			{
				std::cerr << "raw: |" << buffer << "|\n";
				std::vector<std::string>::iterator begin2, end2;
				std::cerr << "message :\n\t";
				begin2 = message.begin();
				end2 = message.end();
				while (begin2 != end2)
				{
					std::cerr << (*begin2) << "\n\t";
					begin2++;
				}
			}
			if (message[0] == "NICK" || message[0] == "USER")
				u.set_real_user(true);
			if (u.get_real_user() == true)
			{
				read = call_command((*this), u, message);
			}
			else
			{
				std::cout << RED << "SERVER COMMAND" << std::endl;
				//TODO nico: Faire la la fcts qui gere la les commandes envoyé par les server.
			}
			
			CGREEN << "Command terminated with code " << read << ENDL;
		}
	}
	
//	FD_CLR(u.get_fd(), &(this->_sockets));
	return (0);
}

int Server::write_socket(int const fd, std::string const &message) const
{
	if (send(fd, message.c_str(), message.size(), 0))
		return (0);
	return (1);
}

int Server::receive_data()
{
	std::list<User>::iterator begin, end, tmp;

	begin = this->_users.begin();
	end = this->_users.end();
	while (begin != end)
	{
		tmp = begin;
		begin++;
		if (FD_ISSET((*tmp).get_fd(), &(this->_sockets)))
		{
			this->read_socket(*tmp);
		}
	}
	return (0);
}

int Server::message_splitter(char *&buffer, std::vector<std::string> &message)
{
	int i;
	int last;
	std::list<int> l;
	std::list<int>::iterator begin, end;
	std::string tmp;

	//find separators
	i = 0;
	while (buffer[i] != 0)
	{
		if (buffer[i] == ':')
		{
			l.push_back(i);
			break ;
		}
		else if (buffer[i] == ' ')
			l.push_back(i);
		else if (buffer[i] == '\r' && buffer[i + 1] == '\n')
		{
			l.push_back(i);
			break ;
		}
		i++;
	}
	message.reserve(l.size());

	//find end of string
	last = i;
	while (buffer[last] != '\r')
	{
		last++;
	}

	begin = l.begin();
	end = l.end();

	//split:
	//	if space/end: take everything from precedent space (or begining) to here
	//	if ':': take everything from after here to the end
	i = 0;
	while (begin != end)
	{
		tmp.erase();
		if (buffer[*begin] != ':')
		{
			tmp.insert(tmp.begin(), (buffer + i), (buffer + (*begin)));
			i = (*begin) + 1;
		}
		else
		{
			tmp.insert(tmp.begin(), buffer + (*begin), buffer + last);
		}
		message.push_back(tmp);
		begin++;
	}
	//buffer will now point after the \r\n.
	//	0 if transmission is finished
	//	other if a second command is in
	buffer += last;
	buffer ++;
	buffer++;
	return (0);
}

int Server::check_connection()
{
	std::list<User>::iterator begin, end, tmp;;
	std::vector<std::string> quit;

	quit.push_back("QUIT");
	quit.push_back(":User Has been detected as unreachable");
	begin = this->_users.begin();
	end = this->_users.end();
	int i;
	char buffer[1];

	while (begin != end)
	{
		std::cerr << "\t\treading...";
		i = recv((*begin).get_fd(), buffer, 1, MSG_PEEK);
		std::cerr << "read:" << i << "\n";
		if (i == 0)
		{
			tmp = begin;
			begin++;
			std::cerr << "A bad read was detected\n";
			QUIT((*this), *tmp, quit);
		}
		else
		{
			begin++;
		}
	}
	return (0);
}

std::string lower(std::string const &str)
{
	std::string res = "";
	int i = 0;
	
	while (str[i] != '\0')
	{
		std::cerr << "\ti:" << i << "\n";
		res[i] = std::tolower(str[i]);
		i++;
	}
	return (res);
}

User *Server::getuserbynick(std::string const nick)
{
	std::list<User>::iterator begin, end;

	begin = this->_users.begin();
	end = this->_users.end();

	while (begin != end)
	{
		//std::cerr << "Lower act nick:" << lower((*begin).get_nickname()) << " looking for lower " << lower(nick) << "\n";
		//if (lower((*begin).get_nickname()) == lower(nick))
		if (((*begin).get_nickname()) == (nick))
			return (&(*begin));
		begin++;
	}
	return (NULL);
}

User *Server::getuserbyfd(int fd)
{
	std::list<User>::iterator begin, end;

	begin = this->_users.begin();
	end = this->_users.end();

	while (begin != end)
	{
		if ((*begin).get_fd() == fd)
			return (&(*begin));
		begin++;
	}
	return (NULL);
}

int Server::disconnect_user(std::list<User>::iterator const &it)
{
	this->_users.erase(it);
	//message: user has disconnected;
	CYELLOW << "an User as disconnected" << ENDL;
	return (0);
}

int Server::disconnect_user(User const &u)
{
	std::list<User>::iterator begin, end;
	
	begin = this->_users.begin();
	end = this->_users.end();
	std::cerr << "nb_user: " << this->_users.size() << "\n";
	while ((*begin).get_fd() != u.get_fd() && begin != end)
		begin++;

	if (begin == end)
	{
		std::cerr << RED << "Can not disconnect user: not found" << ENDL;
exit(-1);
		return (-1);
	}
	this->_users.erase(begin);
	//message: user has disconnected;
	CYELLOW << "an User has disconnected" << ENDL;
	return (0);
}

std::list<Channel>::iterator Server::add_channel(std::string name, std::string password)
{
	this->_channels.push_back(Channel(name, password));
	
	return (--(this->_channels.end()));
}

int Server::delete_channel(std::string name)
{
	std::list<Channel>::iterator begin, end;

	begin = this->_channels.begin();
	end = this->_channels.end();

	while (begin != end)
	{
		if ((*begin).str_name() == name)
		{
			this->_channels.erase(begin);
			break ;
		}
		begin++;
	}
	return (this->_channels.size());
}

std::list<Channel>::iterator Server::find_channel(char prefix, std::string name)
{
	std::list<Channel>::iterator begin, end;

	begin = this->_channels.begin();
	end = this->_channels.end();

	while (begin != end)
	{
		if ((*begin).get_prefix() == prefix && (*begin).get_name() == name)
			break ;
		begin++;
	}
	return (begin);
}















