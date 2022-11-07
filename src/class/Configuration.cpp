/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:34:21 by fboumell          #+#    #+#             */
/*   Updated: 2022/11/07 16:48:46 by fboumell         ###   ########.fr       */
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
	o << "___________________________________" << std::endl;
	o << std::endl;
	o << "\033[35m" << "	Configuration Infos" << "\033[0m" << std::endl;
	o << "___________________________________" << std::endl;
	o << std::endl;
	o << "\033[36m" << "ServerName	" << "\033[0m" << " |"  << " " << "\033[34m" << i.getServerName() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
	o << "\033[36m" << "ServerVersion	" << "\033[0m" << " |" << " " << "\033[34m" << i.getServerVersion() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
	o << "\033[36m" << "Motd		" << "\033[0m" << " |" << " " <<  "\033[34m" << i.getMotd() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
	o << "\033[36m" << "InfoConfig	" << "\033[0m" << " |" << " " << "\033[34m" << i.getInfoConfig() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
	o << "\033[36m" << "OperUser	" << "\033[0m" << " |" << " " << "\033[34m" << i.getOperUSer() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
	o << "\033[36m" << "OperPass	" << "\033[0m" << " |" << " " << "\033[34m" << i.getOperPass() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
	o << "\033[36m" << "Ping		" << "\033[0m" << " |" << " " << "\033[34m" << i.getPing() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
	o << "\033[36m" << "Timeout		" << "\033[0m" << " |" << " " << "\033[34m" << i.getTimeout() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
	o << "\033[36m" << "Backlogs	" << "\033[0m" << " |" << " " << "\033[34m" << i.getMaxBacklogs() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
	o << "\033[36m" << "MaxUsers	" << "\033[0m" << " |"  << " " << "\033[34m" << i.getMaxUsers() << "\033[0m" << std::endl;
	o << "-----------------------------------" << std::endl;
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