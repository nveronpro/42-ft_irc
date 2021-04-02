/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UModes.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:29:45 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/11 16:31:23 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UMODES_HPP
# define UMODES_HPP

#include <string>

class UModes
{
	private:
		bool _a;	//away
		bool _i;	//invisible
		bool _w;	//walops
		bool _r;	//restricted
		bool _o;	//operator
		bool _O;	//local Operator
		bool _s;	//server notices

	public:
		UModes();

		UModes(UModes const &u);

		bool get_a() const;
		bool get_i() const;
		bool get_w() const;
		bool get_r() const;
		bool get_o() const;
		bool get_O() const;
		bool get_s() const;

		UModes update(std::string const &str);

		void set_a(bool param = true);
		void set_o(bool param = true);
		void set_O(bool param = true);
		void set_r(bool param = true);
		void set(int i);

		UModes operator=(UModes const &u);

		UModes operator-(char const c);
		UModes operator-=(char const c);

		UModes operator+(char const c);
		UModes operator+=(char const c);
};

#endif