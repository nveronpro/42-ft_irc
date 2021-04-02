/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UModes.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroberts <oroberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:29:15 by oroberts          #+#    #+#             */
/*   Updated: 2021/03/11 16:32:39 by oroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/UModes.hpp"

UModes::UModes() : _a(0), _i(0), _w(0), _r(0), _o(0), _O(0), _s(0)
{
	return ;
}

UModes::UModes(UModes const &u) : _a(u._a), _i(u._i), _w(u._w), _r(u._r), _o(u._o), _O(u._O), _s(u._s)
{
	return ;
}

bool UModes::get_a() const {return (this->_a);}
bool UModes::get_i() const {return (this->_i);}
bool UModes::get_w() const {return (this->_w);}
bool UModes::get_r() const {return (this->_r);}
bool UModes::get_o() const {return (this->_o);}
bool UModes::get_O() const {return (this->_O);}
bool UModes::get_s() const {return (this->_s);}

UModes UModes::update(std::string const &str)
{
	int i = 0;

	if (str[0] == '+')
	{
		while(str[i])
		{
			(*this) += str[i++];
		}
	}
	else if (str[0] == '-')
	{
		while(str[i])
		{
			(*this) -= str[i++];
		}
	}
	return (*this);
}

void UModes::set_a(bool param) {this->_a = param;}
void UModes::set_o(bool param) {this->_o = param;}
void UModes::set_O(bool param) {this->_O = param;}
void UModes::set_r(bool param) {this->_r = param;}
void UModes::set(int i)
{
	i /= 4;
	if (i % 2 == 1)
	{
		(*this) += 'w';
		i--;
	}
	i /= 2;
	if (i % 2 == 1)
	{
		(*this) += 'i';
		i--;
	}
}

UModes UModes::operator=(UModes const &u)
{
	this->_a = u._a;
	this->_i = u._i;
	this->_w = u._w;
	this->_r = u._r;
	this->_o = u._o;
	this->_O = u._O;
	this->_s = u._s;

	return (*this);
}

UModes UModes::operator-(char const c)
{
	UModes ret(*this);

	ret -= c;
	return (ret);
}

UModes UModes::operator-=(char const c)
{
	//if (c == 'a')			//should not be used normally
	//	this->_a = false;
	if (c == 'i')
		this->_i = false;
	else if (c == 'w')
		this->_w = false;
	//else if (c == 'r')	//should not be used normally
	//	this->_r = false;
	else if (c == 'o')
		this->_o = false;
	else if (c == 'O')
		this->_O = false;
	else if (c == 's')
		this->_s = false;
	return (*this);
}

UModes UModes::operator+(char const c)
{
	UModes ret(*this);

	ret += c;
	return (ret);
}

UModes UModes::operator+=(char const c)
{
	//if (c == 'a')			//should not be used normally
	//	this->_a = true;
	if (c == 'i')
		this->_i = true;
	else if (c == 'w')
		this->_w = true;
	else if (c == 'r')
		this->_r = true;
	//else if (c == 'o')	//should not be used normally
	//	this->_o = true;
	//else if (c == 'O')	//should not be used normally
	//	this->_O = true;
	else if (c == 's')
		this->_s = true;
	return (*this);
}
