/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/25 15:12:41 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client() : _fd(-1), _addr(sockaddr())
{
}

Client::Client( const Client & src ) : _fd(-1), _addr(sockaddr())
{
	(void)src;
}

Client::Client(sockfd fd, struct sockaddr addr, std::string servername) : _fd(fd), _addr(addr), _servername(servername), _connected(true),  _authorize(false), _adm(false), _nickname(), _username(), _realname(), _buffer()
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Client::~Client()
{
	close(this->_fd);
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
	(void)rhs;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Client const & i )
{
	o << "Client at socket #" << i.getFd() << " has nickname: " << i.getNickname();
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	Client::send_to(std::string msg) const
{
	std::cout << "Message to client #" << this->_fd << " (" << this->_nickname << ") >> [" << msg << "]" << std::endl;
	msg += "\r\n";
	send(this->_fd, msg.c_str(), strlen(msg.c_str()), MSG_NOSIGNAL);
}

void	Client::disconnect(void)
{
	this->_connected = false;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
sockfd						Client::getFd(void) const
{
	return this->_fd;
}

struct sockaddr const&	Client::getAddr(void) const
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

bool			Client::getAuthorize(void) const
{
	return this->_authorize;
}

std::string const&	Client::getBuffer(void) const
{
	return this->_buffer;
}

bool	Client::getConnected(void) const
{
	return this->_connected;
}

void			Client::setNickname(std::string new_nick)
{
	this->_nickname = new_nick;
}

void			Client::setUsername(std::string new_nick)
{
	this->_username = new_nick;
}

void	Client::setRealname(std::string new_nick)
{
	this->_realname = new_nick;
}

void	Client::setAdm(bool	new_adm)
{
	this->_adm = new_adm;
}

void	Client::setBuffer(std::string new_buffer)
{
	this->_buffer = new_buffer;
}

void	Client::setAuthorize(bool	authorization)
{
	this->_authorize = authorization;
}

/* ************************************************************************** */
