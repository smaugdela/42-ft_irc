/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/07 18:20:05 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client() : _fd(-1)
{
}

Client::Client( const Client & src ) : _fd(-1)
{
	(void)src;
}

Client::Client(sockfd fd, struct sockaddr_in addr, std::string servername) : _fd(fd), _connected(true), _servername(servername), _authorize(false), _nickname(), _username(), _realname(), _buffer(), _last_com(time(0)), _mode("w")
{
	char hostname[NI_MAXHOST];

	_hostaddr = inet_ntoa(addr.sin_addr);

	if (getnameinfo((struct sockaddr *)&addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, 0) != 0)
		shield(true, true, "getnameinfo", __FILE__, __LINE__);
	else
		_hostname = hostname;
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

void	Client::disconnect(void)
{
	this->_connected = false;
}

void	Client::send_to(std::string msg_str) const
{
	msg_str = getPrefix() + " " + msg_str;
	my_send(this, msg_str);
}

void	Client::welcome(Server *serv) const
{
	std::string	str;

	str = RPL_WELCOME;
	str += " " + _nickname + " Welcome to the Internet Relay Network " + _nickname + "!" + _username + "@" + _hostname;
	send_to(str);
	str = RPL_YOURHOST;
	str += " " + _nickname + " Your host is " + serv->getConfig()->getServerName() + ", running version " + serv->getConfig()->getServerVersion();
	send_to(str);
	str = RPL_CREATED;
	str += " " + _nickname + " This server was created " + std::string(ctime(&(serv->getCreateDate())));
	send_to(str);
	str = RPL_MYINFO;
	str += " " + _nickname + " " + serv->getConfig()->getServerName() + " " + serv->getConfig()->getServerVersion() + " Oowi *none*";
	send_to(str);
	Message	msg(serv->getUser(_fd), NULL, "MOTD");
	motd(serv, msg);
}

void	Client::resetTime(void)
{
	_last_com = time(0);
}

size_t	Client::getLastcom(void) const
{
	return (time(0) - this->_last_com);
}

std::string	Client::getPrefix(void) const
{
	std::string	prefix = "";

	if (_nickname.size())
	{
		prefix = ":" + _nickname;
		if (_username.size())
			prefix += "!" + _username;
		if (_hostname.size())
			prefix += "@" + _hostname;
		else
			prefix += "@" + _hostaddr;
	}
	else
		prefix = ":" + _servername;
	return (prefix);
}

void Client::addMode(char mode)
{
	if (this->_mode.find(mode) == std::string::npos)
		this->_mode += mode;
	else
		return ;
}

void Client::rmMode(char mode)
{
	if (this->_mode.find(mode) != std::string::npos)
		this->_mode.erase(this->_mode.find(mode), 1);
	else
		return ;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

sockfd					Client::getFd(void) const
{
	return this->_fd;
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

std::string const &Client::getMode(void) const
{
	return this->_mode;
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

void	Client::setBuffer(std::string new_buffer)
{
	this->_buffer = new_buffer;
}

void	Client::setAuthorize(bool	authorization)
{
	this->_authorize = authorization;
}

/* ************************************************************************** */
