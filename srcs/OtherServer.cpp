/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtherServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <nveron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:30:24 by nveron            #+#    #+#             */
/*   Updated: 2021/03/22 13:36:28 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/OtherServer.hpp"

int	connect_to_host(Server *serv)
{
	int sock = 0;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
		std::cout << "Socket creation error " << std::endl;

        return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv->get_hostport());
    if(inet_pton(AF_INET, serv->get_hostname().c_str(), &serv_addr.sin_addr)<=0) 
    {
		std::cout << "Invalid address/ Address not supported" << std::endl;
        return 1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
		std::cout << "Connection Failed" << std::endl;
        return 1;
    }
	std::cout << GREEN << "Connection to " << serv->get_hostname() << ":" << serv->get_hostport() << " operational" << ENDL;
	serv->set_hostsocket(sock);
	int valread;
	char buffer[1024] = {0};
	int i;
	std::string ms = "PASS password\r\n";
	i = send(sock , ms.c_str(), ms.size() , 0 );
	std::cout <<GREEN << "ok" << ENDL;
	ms = "SERVER ft_irc 1 :irc.example.net Info Text\r\n";
	i = send(sock , ms.c_str(), ms.size() , 0 );
	if (i < 0)
		std::cout << RED << "ERROR" << ENDL;
	while ((valread = read(sock , buffer, 1024)) > 0)
	{
		std::cout << buffer << std::endl;
	}
    return 0;
}

int		cut_string(char **str)
{
	for (int i = 0; (*str)[i]; i++)
	{
		if ((*str)[i] == ':')
		{
			(*str)[i] = '\0';
			return (i + 1);
		}
	}
	return (0); // no ':' found 
}

void	server_network_information(Server *serv, char *str)
{
	(void)serv;
	int start;

	char *host = str;
	start = cut_string(&host);
	char *port = str + start;
	char *password = str + cut_string(&port) + start;

	serv->set_hostname(host);
	serv->set_hostport(atoi(port));
	serv->set_hostpassword(password);
}

int	load_information(int argc, char **argv, Server *serv)
{
	if (argc == 3)
	{
		serv->set_port(atoi(argv[1]));
		serv->set_password(argv[2]);
		serv->set_name("my_serv");
	}
	else if (argc == 4)
	{
		server_network_information(serv, argv[1]);
		serv->set_port(atoi(argv[2]));
		serv->set_password(argv[3]);
		serv->set_name("my_serv");
	}
	else
		return (1);
	return (0);
}