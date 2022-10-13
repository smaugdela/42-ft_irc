/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/13 18:11:40 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client()
{
}

Client::Client( const Client & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Client::~Client()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Client &				Client::operator=( Client const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Client const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/
sockfd						Client::getFd(void) const
{
	return this->_fd;
}

struct sockaddr_in const &Client::getAddr(void) const
{
	return this->_addr;
}

std::string const &Client::getNickname(void) const
{
	return this->_nickname;
}

std::string const &Client::getUsername(void) const
{
	return this->_username;
}

std::string const &Client::getRealname(void) const
{
	return this->_realname;
}

bool			Client::getAdm(void) const
{
	return this->_adm;
}

void			Client::setNickname(std::string new_nick)
{
	this->_nickname = new_nick;
}

void			Client::setUsername(std::string new_nick)
{
	this->_username = new_nick;
}

void			Client::setRealname(std::string new_nick)
{
	this->_realname = new_nick;
}

void			Client::setAdm(bool	new_adm)
{
	this->_adm = new_adm;
}

/* ************************************************************************** */
