/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CModes.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:28:42 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/22 17:06:15 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMODES_HPP
# define CMODES_HPP

/*
**	Channel modes:
**	O: give "Channel creator" status (only for safe channels)
**	o: give/take channel operator privilege
**	v: give/take the voice privilege: right to talk on moderated channels
**
**	a: anonymous channel flag: all from anonymous@anonymous!anonymous
	**	TODO: Block anonymous from available nicks
	**	&: can be toggled on/off by chop
	**	!: Can be toggled on(NOT OFF) by channel creators
	**	other: NOT AVAILABLE
	**	WHOIS, WHO, NAMES must hide other users on channel
**	i: invite-only channel flag: new members must match the mask OR be invinted by chop. Restricts the use of INVITE
**	m: moderated channel: Users must be chop, OP of have the voice privilege to speak
**	n: no messages to channel from clients on the outside: Only users on channel may send messages
**	
**	q: quiet channel flag: message from NICK, JOINs and PARTs not sent to channel
**	p: private channel flag: hidden in WHOIS, 
**	s: secret channel flag hidden in WHOIS, TOPIC, LIST, NAMES. will show on MODE command. not accounted in LUSERS
		**	p & s can not be set at the same time. if `MODE p`, silently ignore
**	r: server reop channel flag: `!` only, only by channel creator
		**	if no chop/OP for longer than "reop delay" secondes, op new users in channel
**	t: topic settable by channel operator only flag: Topic restricted to chop
**	
**	k: set/remove the channel key (password): Denied if key not given. seen by `MODE` command
**	l: set/remove the user limit to channel: if max reached denie connection. available to members witch `MODE`
**	
**	b: set/remove ban mask to keep users out
**	e: set/remove an exception mask to override a ban mask
**	I: set/remove an invitation mask to automatically override the invite-only flag
*/
class CModes
{
	private:
		bool _O; //give "Channel creator" status (only for safe channels)
		bool _o; //give/take channel operator privilege
		bool _v; //give/take the voice privilege: right to talk on moderated channels
		bool _a; //anonymous channel flag
		bool _i; //invite-only channel flag: new members must match the mask OR be invinted by chop. Restricts the use of INVITE
		bool _m; //moderated channel: Users must be chop, OP of have the voice privilege to speak
		bool _n; //no messages to channel from clients on the outside: Only users on channel may send messages
		bool _q; //quiet channel flag: message from NICK, JOINs and PARTs not sent to channel
		bool _p; //private channel flag: hidden in WHOIS, 
		bool _s; //secret channel flag hidden in WHOIS, TOPIC, LIST, NAMES. will show on MODE command. not accounted in LUSERS
		bool _r; //server reop channel flag: `!` only, only by channel creator
		bool _t; //topic settable by channel operator only flag: Topic restricted to chop
		bool _k; //set/remove the channel key (password): Denied if key not given. seen by `MODE` command
		bool _l; //set/remove the user limit to channel: if max reached denie connection. available to members witch `MODE`
		bool _b; //set/remove ban mask to keep users out
		bool _e; //set/remove an exception mask to override a ban mask
		bool _I; //set/remove an invitation mask to automatically override the invite-only flag

	public:
		CModes();
		CModes(CModes const &modes);
		CModes &operator=(CModes const &modes);

		bool get_O() const;
		bool get_o() const;
		bool get_v() const;
		bool get_a() const;
		bool get_i() const;
		bool get_m() const;
		bool get_n() const;
		bool get_q() const;
		bool get_p() const;
		bool get_s() const;
		bool get_r() const;
		bool get_t() const;
		bool get_k() const;
		bool get_l() const;
		bool get_b() const;
		bool get_e() const;
		bool get_I() const;

		void set_O(bool val);
		void set_o(bool val);
		void set_v(bool val);
		void set_a(bool val);
		void set_i(bool val);
		void set_m(bool val);
		void set_n(bool val);
		void set_q(bool val);
		void set_p(bool val);
		void set_s(bool val);
		void set_r(bool val);
		void set_t(bool val);
		void set_k(bool val);
		void set_l(bool val);
		void set_b(bool val);
		void set_e(bool val);
		void set_I(bool val);



};

#endif