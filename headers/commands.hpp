/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:03:47 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/23 09:58:09 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include "Server.hpp"

int call_command(Server &serv, User &u, std::vector<std::string> message);

int AWAY(Server &serv, User &u, std::vector<std::string> message);
int JOIN(Server &serv, User &u, std::vector<std::string> message);
int LUSERS(Server &serv, User &u, std::vector<std::string> message);
int MOTD(Server &serv, User &u, std::vector<std::string> message);
int NOTICE(Server &serv, User &u, std::vector<std::string> message);
int NICK(Server &serv, User &u, std::vector<std::string> message);
int PART(Server &serv, User &u, std::vector<std::string> message);
int PING(Server &serv, User &u, std::vector<std::string> message);
int PONG(Server &serv, User &u, std::vector<std::string> message);
int PRIVMSG(Server &serv, User &u, std::vector<std::string> message);
int QUIT(Server &serv, User &u, std::vector<std::string> message);
int USER(Server &serv, User &u, std::vector<std::string> message);
int WHOIS(Server &serv, User &u, std::vector<std::string> message);
int OPER(Server &serv, User &u, std::vector<std::string> message);
int PASS(Server &serv, User &u, std::vector<std::string> message);
int ISON(Server &serv, User &u, std::vector<std::string> message);


#endif