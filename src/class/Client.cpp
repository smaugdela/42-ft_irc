/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/26 11:49:25 by smagdela         ###   ########.fr       */
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

void	Client::send_to(std::string msg_str) const
{
	if (_connected == false || _authorize == false)
		return ;

	if (this->_servername.size())
		msg_str = ":" + this->_servername + " " + msg_str;
	std::cout << "Message to client #" << this->_fd << " (" << this->_nickname << ") >> [" << msg_str << "]" << std::endl;
	msg_str += "\r\n";

	const char*	msg = msg_str.c_str();
	size_t	init_len = strlen(msg);
	size_t	actual_len = 0;
	ssize_t	ret = 0;

	while (actual_len < init_len || (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN)))
	{
		ret = send(this->_fd, &msg[actual_len], init_len - actual_len, MSG_NOSIGNAL);
		if (ret >= 0)
			actual_len += ret;
	}
}

void	Client::disconnect(void)
{
	this->_connected = false;
}

void	Client::welcome(Server *serv) const
{
	std::string	str;

	str = RPL_WELCOME;
	str += " " + _nickname + " :Welcome to the Internet Relay Network " + _nickname + "!" + _username + "@" + _servername;
	send_to(str);
	str = RPL_YOURHOST;
	str += " " + _nickname + " :Your host is " + _servername + ", running version " + serv->getConfig()->getServerVersion();
	send_to(str);
	str = RPL_CREATED;
	str += " " + _nickname + " :This server was created " + std::string(ctime(&(serv->getCreateDate())));
	send_to(str);
	str = RPL_MYINFO;
	str += " " + _nickname + " :" + _servername + " " + serv->getConfig()->getServerVersion() + " *none* *none* ";
	send_to(str);
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
