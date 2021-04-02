/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:49:33 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/24 15:49:01 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP
# include "Server.hpp"
# include "User.hpp"
# include "Channel.hpp"

class User;
class Channel;

std::string itos(int const i);

# define CODE_RPL_WELCOME 001
# define INIT_RPL_WELCOME(NICK, USER, HOST) "Welcome to the Internet Relay Network " + (NICK) + "!" + (USER) + "@" + HOST

# define CODE_RPL_YOURHOST 002
# define INIT_RPL_YOURHOST(SNAME, SVER) std::string(":Your host is ") + SNAME + ", running version " + SVER

# define CODE_RPL_CREATED 003
# define INIT_RPL_CREATED(DATE) ":This server was created " + DATE

# define CODE_RPL_MYINFO 004
# define INIT_RPL_MYINFO(SNAME, SVER, UMODES, CMODES) std::string("ServerName:") + SNAME + ", Version:" + SVER + ", UserModes:" + UMODES + ", ChannelModes:" + CMODES




# define CODE_RPL_LUSERCLIENT 251
# define INIT_RPL_LUSERCLIENT(USERS, SERVICES, SERVERS) ":There are " + itos(USERS) + " users and " + itos(SERVICES) + " services on " + itos(SERVERS) + " servers"

# define CODE_RPL_LUSEROP 252
# define INIT_RPL_LUSEROP(OP) itos(OP) + " :operator(s) online"

# define CODE_RPL_LUSERUNKNOWN 253
# define INIT_RPL_LUSERUNKNOWN(UNKNOWN) itos(UNKNOWN) + " :unknown connection(s)"

# define CODE_RPL_LUSERCHANNELS 254
# define INIT_RPL_LUSERCHANNELS(CHANNELS) itos(CHANNELS) + " :channels formed"

# define CODE_RPL_LUSERME 255
# define INIT_RPL_LUSERME(CLIENTS, SERVERS) ":I have " + itos(CLIENTS) + " clients and " + itos(SERVERS) + " servers"

# define CODE_RPL_AWAY 301
# define INIT_RPL_AWAY(N, MESSAGE) N + " :" + MESSAGE

# define CODE_RPL_UNAWAY 305
# define INIT_RPL_UNAWAY ":You are no longer marked as being away"

# define CODE_RPL_NOWAWAY 306
# define INIT_RPL_NOWAWAY ":You have been marked as being away"

# define CODE_RPL_WHOISUSER 311
# define INIT_RPL_WHOISUSER(NICK, USER, HOST, REAL) NICK + " " + USER  + " " + HOST + " * :" + REAL

# define CODE_RPL_WHOISSERVER 312
# define INIT_RPL_WHOISSERVER(NICK, SERV, SINFOS) NICK + " " + SERV + " :" + SINFOS

# define CODE_RPL_WHOISOPERATOR 313
# define INIT_RPL_WHOISOPERATOR(NICK) NICK + " :is an IRC operator"

# define CODE_RPL_WHOISIDLE 317
# define INIT_RPL_WHOISIDLE(NICK, SECONDS) NICK + " " + SECONDS + " :seconds idle"

# define CODE_RPL_ENDOFWHOIS 318
# define INIT_RPL_ENDOFWHOIS(NICK) NICK + " :End of WHOIS list"

# define CODE_RPL_WHOISCHANNELS 319
# define INIT_RPL_WHOISCHANNELS(NICK, CHANNELS) NICK + " :" + CHANNELS

# define CODE_RPL_MOTD 372
# define INIT_RPL_MOTD(SERVER) ":-" + SERVER + " Message of the day - "

# define CODE_RPL_MOTDSTART 375
# define INIT_RPL_MOTDSTART(TEXT) std::string(":- ") + TEXT

# define CODE_RPL_ENDOFMOTD 376
# define INIT_RPL_ENDOFMOTD ":End of MOTD command"

# define CODE_RPL_YOUREOPER 381
# define INIT_RPL_YOUREOPER(SERVER, NICK) ":server " + SERVER + " " + NICK + " :You are now an IRC operator"

# define CODE_RPL_ISON  303
# define INIT_RPL_ISON(NICK) ": " + NICK





/*
# define CODE_
# define INIT_
*/




# define CODE_RPL_TOPIC 332
# define INIT_RPL_TOPIC(CHANNEL, TOPIC) CHANNEL + " :" + TOPIC
# define CODE_RPL_NAMREPLY 353
# define INIT_RPL_NAMREPLY(CHANNEL, USERS) " = " + CHANNEL + " :" + USERS
# define CODE_RPL_ENDOFNAMES 366
# define INIT_RPL_ENDOFNAMES(CHANNEL) CHANNEL + " : End of NAMES list"
# define CODE_ERR_NOSUCHCHANNEL 403
# define INIT_ERR_NOSUCHCHANNEL(CHANNEL) CHANNEL + " :No such channel"
# define CODE_ERR_TOOMANYCHANNELS 405
# define INIT_ERR_TOOMANYCHANNELS(CHANNEL) CHANNEL + " :You have joined too many channels"
//# define CODE_ERR_TOOMANYTARGETS
# define CODE_ERR_UNAVAILRESOURCE 437
# define INIT_ERR_UNAVAILRESOURCE(NAME) std::string(NAME) + " :Nick/channel is temporarily unavailable"

//# define CODE_ERR_NEEDMOREPARAMS
# define CODE_ERR_CHANNELISFULL 471
# define INIT_ERR_CHANNELISFULL(CHANNEL)  CHANNEL + " :Cannot join channel (+l)"
# define CODE_ERR_INVITEONLYCHAN 473
# define INIT_ERR_INVITEONLYCHAN(CHANNEL) CHANNEL + ":Cannot join channel (+i)"
# define CODE_ERR_BANNEDFROMCHAN 474
# define INIT_ERR_BANNEDFROMCHAN(CHANNEL) + " :Cannot join channel (+b)"
# define CODE_ERR_BADCHANNELKEY 475
# define INIT_ERR_BADCHANNELKEY(CHANNEL) CHANNEL + " :Cannot join channel (+k)"
# define CODE_ERR_BADCHANMASK 476
# define INIT_ERR_BADCHANMASK(CHANNEL) CHANNEL + " :Bad Channel Mask"












/*
**	END
**	OF
**	WORK
**	HOLD
*/





# define CODE_ERR_NOSUCHNICK 401
# define INIT_ERR_NOSUCHNICK(NICK) NICK + " :No such nick/channel"

# define CODE_ERR_NOSUCHSERVER 402
# define INIT_ERR_NOSUCHSERVER(SERVER) SERVER + " :No such server"

# define CODE_ERR_CANNOTSENDTOCHAN 404
# define INIT_ERR_CANNOTSENDTOCHAN(CHANNEL) CHANNEL + " :Cannot send to channel"

# define CODE_ERR_TOOMANYTARGETS 407
# define INIT_ERR_TOOMANYTARGETS(TARGET, NB_RECIPIENTS, ABORT) TARGET + " :" + itos(NB_RECIPIENTS) + " recipients. " + ABORT

# define CODE_ERR_NOORIGIN 409
# define INIT_ERR_NOORIGIN ":No origin specified"

# define CODE_ERR_NORECIPIENT 411
# define INIT_ERR_NORECIPIENT(COMMAND) ":No recipient given (" + COMMAND + ")"

# define CODE_ERR_NOTEXTTOSEND 412
# define INIT_ERR_NOTEXTTOSEND ":No text to send"

# define CODE_ERR_NOTOPLEVEL 413
# define INIT_ERR_NOTOPLEVEL(MASK) MASK + " :No toplevel domain specified"

# define CODE_ERR_WILDTOPLEVEL 414
# define INIT_ERR_WILDTOPLEVEL(MASK) MASK + " :Wildcard in toplevel domain"

# define CODE_ERR_UNKNOWNCOMMAND 421
# define INIT_ERR_UNKNOWNCOMMAND(COMMAND) COMMAND + " :Unknown command"

# define CODE_ERR_NOMOTD 422
# define INIT_ERR_NOMOTD ":MOTD File is missing"

# define CODE_ERR_NONICKNAMEGIVEN 431
# define INIT_ERR_NONICKNAMEGIVEN ":No nickname given"

# define CODE_ERR_NICKNAMEINUSE 433
# define INIT_ERR_NICKNAMEINUSE(NICK) NICK + " :Nickname already in use"

# define CODE_ERR_NOTONCHANNEL 442
# define INIT_ERR_NOTONCHANNEL(CHAN) CHAN + " :You're not on that channel"


# define CODE_ERR_NOTREGISTERED 451
# define INIT_ERR_NOTREGISTERED ":You have not registered"

# define CODE_ERR_NEEDMOREPARAMS 461
# define INIT_ERR_NEEDMOREPARAMS(COMMAND) COMMAND + " :Not enouch parameters"

# define CODE_ERR_ALREADYREGISTRED 462
# define INIT_ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"

# define CODE_ERR_PASSWDMISMATCH 464
# define INIT_ERR_PASSWDMISMATCH ":Password missmatch"

int send_reply(int code, Server &s, User &u, std::vector<std::string> const &message, std::vector<std::string> const &other = std::vector<std::string>());
std::string build_reply(int code, Server &s, User &u, std::vector<std::string> const &message, std::vector<std::string> const &other = std::vector<std::string>());


#endif