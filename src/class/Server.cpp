/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/17 13:03:32 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server() //private
{
	std::cout << "Server hasn't been initialised yet." << std::endl;
}

Server::Server(int ac, const char **av) // public
{
	shield(parse_input(ac, av, this), false, "Usage: ./ircserv <port> <password>", __FILE__, __LINE__);

	std::ifstream	ifs;

	ifs.open("/proc/sys/net/ipv4/tcp_max_syn_backlog");
	if (ifs.fail())
		this->_max_backlogs = MAX_BACKLOGS;
	else
		ifs >> this->_max_backlogs;
	ifs.close();

	this->_listener = start_listening(this);
}

Server::Server( const Server & src ) // private
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Server &				Server::operator=( Server const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Server const & i )
{
	// o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

bool	Server::addUser(Client* new_user)
{
	this->_users.insert(std::make_pair(new_user->getFd(), new_user));
}

bool Server::rmUser(Client* user)
{
	this->_user.erase(user->getfd());
}

Client *Server::getUser(socket fd) const
{
	return (this->_users[fd]);
}

Client *Server::getUser(std::string nickname) const
{
	return (this->_users[nickname]);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int 				Server::getPort(void) const
{
	return this->_port;
}

std::string const 	&Server::getPassword(void) const
{
	return this->_password;
}

size_t				Server::getMaxbacklogs(void) const
{
	return this->_max_backlogs;
}

sockfd				Server::getListener(void) const
{
	return this->_listener;
}

std::map<sockfd, Client*> const &Server::getUsers(void) const 
{
	return this->_users; 
}

std::map<std::string, Channel*> const &Server::getChans(void) const 
{
	return this->_chans;
}


Client* Server::getUser(sockfd fd) const
{

}

Client*	Server::getUser(std::string nickname) const
{
	
}

void	Server::setPort(int port)
{
	this->_port = port;
}

void	Server::setPassword(std::string password)
{
	this->_password = password;
}

void	Server::setMaxbacklogs(size_t log)
{
	this->_max_backlogs = log;
}

void	Server::setListener(sockfd listener)
{
	this->_listener = listener;
}


/* ************************************************************************** */
