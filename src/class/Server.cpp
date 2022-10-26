/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/26 14:09:11 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server() //private
{
	std::cout << "Server hasn't been initialised yet." << std::endl;
}

Server::Server(int ac, const char **av) // public
{
	_create_date = time(0);
	shield(parse_input(ac, av, this), false, "Usage: ./ircserv <port> <password>", __FILE__, __LINE__);
	this->_config = new Configuration();
	this->_listener = start_listening(this);
	setCmdlist();
}

Server::Server( const Server & src ) // private
{
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
	size_t size = this->_users.size();
	for (size_t i = 0; i < size ; ++i)
	{
		if (this->_users.begin() == this->_users.end())
			break;
		rmUser(this->_users.begin()->second);
	}
	delete this->_config;
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
	(void)rhs;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Server const & i )
{
	o << "Port: " << i.getPort() << " Password: " << i.getPassword();
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool	Server::addUser(Client* new_user)
{
	if (new_user == NULL)
		return false;
	try
	{
		this->_users.at(new_user->getFd());
	}
	catch(const std::out_of_range &e)
	{
		this->_users.insert(std::make_pair(new_user->getFd(), new_user));
		return true;
	}
	return false;
}

void Server::rmUser(Client* user)
{
	if (user != NULL)
	{
		this->_users.erase(user->getFd());
		delete user;
	}
}

Client *Server::getUser(sockfd fd) const
{
	std::map<sockfd, Client*>::const_iterator	ret;

	ret = _users.find(fd);
	if (ret == _users.end())
		return NULL;
	return ret->second;
}

Client *Server::getUser(std::string nickname) const
{
	std::map<sockfd, Client*>::const_iterator	it;

	for (it = _users.begin(); it != _users.end(); ++it)
		if (it->second->getNickname() == nickname)
			break ;
	if (it == _users.end())
		return NULL;
	return it->second;
}

Channel*	Server::getChannel(std::string name) const
{
	std::map<std::string, Channel*>::const_iterator	ret;

	ret = _chans.find(name);
	if (ret == _chans.end())
		return NULL;
	return ret->second;
}

void	Server::broadcast(std::string msg_str) const
{
	std::map<sockfd, Client*>::const_iterator it;

	for (it = _users.begin(); it != _users.end(); ++it)
		it->second->send_to(msg_str);
}

void	Server::setCmdlist()
{
	this->_cmdList.insert(std::make_pair("INFO", info));
	this->_cmdList.insert(std::make_pair("JOIN", join));
	this->_cmdList.insert(std::make_pair("KICK", kick));
	this->_cmdList.insert(std::make_pair("KILL", my_kill));
	this->_cmdList.insert(std::make_pair("LIST", list));
	this->_cmdList.insert(std::make_pair("MOTD", motd));
	this->_cmdList.insert(std::make_pair("NAMES", names));
	this->_cmdList.insert(std::make_pair("NICK", nick));
	this->_cmdList.insert(std::make_pair("OPER", oper));
	this->_cmdList.insert(std::make_pair("PART", part));
	this->_cmdList.insert(std::make_pair("PASS", pass));
	this->_cmdList.insert(std::make_pair("PING", ping));
	this->_cmdList.insert(std::make_pair("PONG", pong));
	this->_cmdList.insert(std::make_pair("PRIVMSG", privmsg));
	this->_cmdList.insert(std::make_pair("QUIT", quit));
	this->_cmdList.insert(std::make_pair("USER", user));
	this->_cmdList.insert(std::make_pair("VERSION", version));
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

sockfd				Server::getListener(void) const
{
	return this->_listener;
}

std::map<sockfd, Client*> const &Server::getUsers(void) const 
{
	return this->_users; 
}

std::map<std::string, Channel*> const& Server::getChans(void) const 
{
	return this->_chans;
}

std::map<std::string, ft_cmd> const& Server::getCmdList(void) const
{
	return this->_cmdList;
}

Configuration*	Server::getConfig(void) const
{
	return this->_config;
}

time_t const&	Server::getCreateDate(void) const
{
	return (this->_create_date);
}

void	Server::setPort(int port)
{
	this->_port = port;
}

void	Server::setPassword(std::string password)
{
	this->_password = password;
}

void	Server::setListener(sockfd listener)
{
	this->_listener = listener;
}

/* ************************************************************************** */
