/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtherServer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <nveron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:30:24 by nveron            #+#    #+#             */
/*   Updated: 2021/03/22 13:36:28 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHERSERVER_HPP
# define OTHERSERVER_HPP

#include "Server.hpp"

int     connect_to_host(Server *serv);
int		cut_string(char **str);
int     load_information(int argc, char **argv, Server *serv);
void	server_network_information(Server *serv, char *str);

#endif
