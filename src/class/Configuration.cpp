/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:34:21 by fboumell          #+#    #+#             */
/*   Updated: 2022/10/24 15:53:27 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Configuration::Configuration() //public
{
	setConfigData(this);
}

Configuration::Configuration( const Configuration & src ) //private
{
	(void)src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Configuration::~Configuration()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Configuration &				Configuration::operator=( Configuration const & rhs ) //private
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	(void)rhs;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Configuration const & i )
{
	o << "ServerName = " << i.getServerName() << std::endl;
	o << "ServerVersion = " << i.getServerVersion() << std::endl;
	o << "Motd = " << i.getMotd() << std::endl;
	o << "InfoConfig = " << i.getInfoConfig() << std::endl;
	o << "OperUser = " << i.getOperUSer() << std::endl;
	o << "OperPass = " << i.getOperPass() << std::endl;
	o << "Ping = " << i.getPing() << std::endl;
	o << "Timeout = " << i.getTimeout() << std::endl;
	o << "Backlogs = " << i.getMaxBacklogs() << std::endl;
	o << "MaxUsers = " << i.getMaxUsers() << std::endl;
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/
std::string const &Configuration::getServerName(void) const
{
	return this->_serverName;
}

std::string const &Configuration::getServerVersion(void) const
{
	return this->_serverVersion;
}

std::string const &Configuration::getMotd(void) const
{
	return this->_motd;
}

std::string const &Configuration::getInfoConfig(void) const
{
	return this->_infoConfig;
}

std::string const &Configuration::getOperUSer(void) const
{
	return this->_operUser;
}

std::string const &Configuration::getOperPass(void) const
{
	return this->_operPass;
}

size_t	Configuration::getPing(void) const
{
	return this->_ping;
}

int		Configuration::getTimeout(void) const
{
	return this->_timeout;
}

size_t	Configuration::getMaxBacklogs(void) const
{
	return this->_maxBacklogs;
}

size_t	Configuration::getMaxUsers(void) const
{
	return this->_maxUsers;
}

void	Configuration::setServerName(std::string serverName)
{
	this->_serverName = serverName;
}

void	Configuration::setServerVersion(std::string serverVersion)
{
	this->_serverVersion = serverVersion;
}

void	Configuration::setMotd(std::string motd)
{
	this->_motd = motd;
}

void	Configuration::setInfoConfig(std::string infoConfig)
{
	this->_infoConfig = infoConfig;
}

void	Configuration::setOperUser(std::string OperUser)
{
	this->_operUser = OperUser;
}

void	Configuration::setOperPass(std::string OperPass)
{
	this->_operPass = OperPass;
}

void	Configuration::setPing(size_t ping)
{
	this->_ping = ping;
}

void	Configuration::setTimeout(int timeOut)
{
	this->_timeout = timeOut;
}

void	Configuration::setMaxBacklogs(size_t maxBacklogs)
{
	this->_maxBacklogs = maxBacklogs;
}

void	Configuration::setMaxUsers(size_t maxUsers)
{
	this->_maxUsers = maxUsers;
}
/* ************************************************************************** */