/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:36:20 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/22 17:18:03 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

#ifndef PATH_TO_MOTD
# define PATH_TO_MOTD "./data/motd.txt"
#endif

void	load_MOTD(Server *serv)
{
	int fd_motd;
	char buffer[513];

	fd_motd = open(PATH_TO_MOTD, O_RDONLY);
	if (fd_motd == -1)
		serv->set_motd("");
	else
	{
		for (int i = 0; i < 513; i++)
			buffer[i] = 0;
		read(fd_motd, buffer, 512);
		serv->set_motd(std::string(buffer));
	}
}

int main(int argc, char **argv)
{
	Server serv(0000, "ft_irc");
	if (load_information(argc, argv, &serv))
	{
		std::cerr << "Usage: " << argv[0] <<" [host:port:password] <port> <password>" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		if (argc == 4 && connect_to_host(&serv))
			exit(EXIT_FAILURE);
		load_MOTD(&serv);

		std::cout << "Initialized server...\n";
		serv.init_server();
		std::cout << "Started server...\n";
		serv.start_server();
	}
	return (0);
}