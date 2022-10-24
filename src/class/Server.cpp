/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/24 13:31:21 by ajearuth         ###   ########.fr       */
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
	shield(parse_input(ac, av, this), false, "Usage: ./ircserv <port> <password>", __FILE__, __LINE__);
	this->_listener = start_listening(this);
	setConfigData(this);
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

Client *Server::getUser(sockfd fd) const
{
	Client *ret;

	try
	{
		ret = this->_users.at(fd);	
	}
	catch(const std::out_of_range &e)
	{
		return NULL;
	}
	return (ret);
}

Client *Server::getUser(std::string nickname) const
{
	std::map<sockfd, Client*>::const_iterator	it;

	for (it = this->_users.begin(); it != this->_users.end(); ++it)
		if (it->second->getNickname() == nickname)
			break ;
	if (it == this->_users.end())
		return NULL;
	return it->second;
}

std::map<std::string, void (*)(Server*, Message&)> const& Server::getCmdList(void) const
{
	return this->_cmdList;
}

std::string const &Server::getServerName(void) const
{
	return this->_serverName;
}

std::string const &Server::getServerVersion(void) const
{
	return this->_serverVersion;
}

std::string const &Server::getMotd(void) const
{
	return this->_motd;
}

std::string const &Server::getInfoConfig(void) const
{
	return this->_infoConfig;
}

std::string const &Server::getOperUSer(void) const
{
	return this->_operUser;
}

std::string const &Server::getOperPass(void) const
{
	return this->_operPass;
}

std::string const &Server::getPing(void) const
{
	return this->_ping;
}

std::string const &Server::getTimeout(void) const
{
	return this->_timeout;
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

void	Server::setServerName(std::string serverName)
{
	this->_serverName = serverName;
}

void	Server::setServerVersion(std::string serverVersion)
{
	this->_serverVersion = serverVersion;
}

void	Server::setMotd(std::string motd)
{
	this->_motd = motd;
}

void	Server::setInfoConfig(std::string infoConfig)
{
	this->_infoConfig = infoConfig;
}

void	Server::setOperUser(std::string OperUser)
{
	this->_operUser = OperUser;
}

void	Server::setOperPass(std::string OperPass)
{
	this->_operPass = OperPass;
}

void	Server::setPing(std::string ping)
{
	this->_ping = ping;
}

void	Server::setTimeout(std::string timeOut)
{
	this->_timeout = timeOut;
}

void	Server::setCmdlist()
{
	this->_cmdList.insert(std::make_pair("ERROR", error));
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
	this->_cmdList.insert(std::make_pair("PING", ping));
	this->_cmdList.insert(std::make_pair("PONG", pong));
	this->_cmdList.insert(std::make_pair("PRIVMSG", privmsg));
	this->_cmdList.insert(std::make_pair("QUIT", quit));
	this->_cmdList.insert(std::make_pair("SQUIT", squit));
	this->_cmdList.insert(std::make_pair("STATS", stats));
	this->_cmdList.insert(std::make_pair("TOPIC", topic));
	this->_cmdList.insert(std::make_pair("USER", user));
}

/* ************************************************************************** */
