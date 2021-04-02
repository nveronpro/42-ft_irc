/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CModes.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:28:24 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/22 17:06:13 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/CModes.hpp"

CModes::CModes()
{
	_O = false;
	_o = false;
	_v = false;
	_a = false;
	_i = false;
	_m = false;
	_n = false;
	_q = false;
	_p = false;
	_s = false;
	_r = false;
	_t = false;
	_k = false;
	_l = false;
	_b = false;
	_e = false;
	_I = false;
}
CModes::CModes(CModes const &modes)
{
	(*this) = modes;
}
CModes &CModes::operator=(CModes const &modes)
{
	_O = modes._O;
	_o = modes._o;
	_v = modes._v;
	_a = modes._a;
	_i = modes._i;
	_m = modes._m;
	_n = modes._n;
	_q = modes._q;
	_p = modes._p;
	_s = modes._s;
	_r = modes._r;
	_t = modes._t;
	_k = modes._k;
	_l = modes._l;
	_b = modes._b;
	_e = modes._e;
	_I = modes._I;

	return (*this);
}

bool CModes::get_O() const {return (this->_O);}
bool CModes::get_o() const {return (this->_o);}
bool CModes::get_v() const {return (this->_v);}
bool CModes::get_a() const {return (this->_a);}
bool CModes::get_i() const {return (this->_i);}
bool CModes::get_m() const {return (this->_m);}
bool CModes::get_n() const {return (this->_n);}
bool CModes::get_q() const {return (this->_q);}
bool CModes::get_p() const {return (this->_p);}
bool CModes::get_s() const {return (this->_s);}
bool CModes::get_r() const {return (this->_r);}
bool CModes::get_t() const {return (this->_t);}
bool CModes::get_k() const {return (this->_k);}
bool CModes::get_l() const {return (this->_l);}
bool CModes::get_b() const {return (this->_b);}
bool CModes::get_e() const {return (this->_e);}
bool CModes::get_I() const {return (this->_I);}

void CModes::set_O(bool val) {this->_O = val;}
void CModes::set_o(bool val) {this->_o = val;}
void CModes::set_v(bool val) {this->_O = val;}
void CModes::set_a(bool val) {this->_a = val;}
void CModes::set_i(bool val) {this->_i = val;}
void CModes::set_m(bool val) {this->_m = val;}
void CModes::set_n(bool val) {this->_n = val;}
void CModes::set_q(bool val) {this->_q = val;}
void CModes::set_p(bool val) {if (!(this->_s)) this->_p = val;}
void CModes::set_s(bool val) {if (!(this->_p)) this->_s = val;}
void CModes::set_r(bool val) {this->_r = val;}
void CModes::set_t(bool val) {this->_t = val;}
void CModes::set_k(bool val) {this->_k = val;}
void CModes::set_l(bool val) {this->_l = val;}
void CModes::set_b(bool val) {this->_b = val;}
void CModes::set_e(bool val) {this->_e = val;}
void CModes::set_I(bool val) {this->_I = val;}