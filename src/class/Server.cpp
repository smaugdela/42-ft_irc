/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/07 17:25:21 by fboumell         ###   ########.fr       */
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

Server::Server(int ac, const char **av)	// public
{
	_create_date = time(0);
	srand(time(NULL));
	shield(parse_input(ac, av, this), false, "Usage: ./ircserv <port> <password>", __FILE__, __LINE__);
	this->_config = new Configuration();
	this->_listener = start_listening(this);
	std::cout << "\033[36m" << "Server IP address" << "\033[0m" << "|" << " " << "\033[34m" << _ipaddr << "\033[0m\n" << std::endl;
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
	close(_listener);
	broadcast("QUIT :Server shutdown");
	size_t size = this->_users.size();
	for (size_t i = 0; i < size ; ++i)
	{
		if (this->_users.begin() == this->_users.end())
			break;
		rmUser(this->_users.begin()->second);
	}
	size = _chans.size();
	for (size_t i = 0; i < size ; ++i)
	{
		if (this->_chans.begin() == this->_chans.end())
			break;
		rmChan(_chans.begin()->second);
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
	{
		if (it->second->getNickname() == nickname)
			break ;
	}
	if (it == _users.end())
		return NULL;
	return it->second;
}

void	Server::addChan(Channel *new_chan)
{
	if (new_chan == NULL)
		return ;
	else if (_chans.find(new_chan->getName()) == _chans.end())
		_chans.insert(std::make_pair(new_chan->getName(), new_chan));
	else
		delete new_chan;
}

Channel*	Server::getChannel(std::string name) const
{
	std::map<std::string, Channel*>::const_iterator	ret;

	for (ret = this->_chans.begin(); ret != this->_chans.end(); ret++)
	{
		if (ret->second->getName() == name && ret->first == name)
			break ;
	}

	if (ret == this->_chans.end())
		return NULL;
	return ret->second;
}

void	Server::rmChan(Channel *chan)
{
	if (chan != NULL)
	{
		_chans.erase(chan->getName());
		delete chan;
	}
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
	this->_cmdList.insert(std::make_pair("MODE", mode));
	this->_cmdList.insert(std::make_pair("MOTD", motd));
	this->_cmdList.insert(std::make_pair("NAMES", names));
	this->_cmdList.insert(std::make_pair("NICK", nick));
	this->_cmdList.insert(std::make_pair("OPER", oper));
	this->_cmdList.insert(std::make_pair("PART", part));
	this->_cmdList.insert(std::make_pair("PASS", pass));
	this->_cmdList.insert(std::make_pair("PING", ping));
	this->_cmdList.insert(std::make_pair("PRIVMSG", privmsg));
	this->_cmdList.insert(std::make_pair("QUIT", quit));
	this->_cmdList.insert(std::make_pair("USER", user));
	this->_cmdList.insert(std::make_pair("VERSION", version));
	this->_cmdList.insert(std::make_pair("NOTICE", notice));
	this->_cmdList.insert(std::make_pair("WALLOPS", wallops));
}

void Server::_callbot(Channel *channel, Client *user, char *message)
{
	std::string bot = "DistinguichCatBot";
	std::string str;
	

	 // Proteger channel user et message 
	 
	if (message[0] != '!')
	{
		str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : Invalid request," + user->getNickname() + "use !help for more informations.";
		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
	}
	std::list<std::string> args = split(message, " ");
	std::list<std::string>::iterator it = args.begin();
	if ((*it).compare("!love") == 0)
	{
		unsigned int nbr = rand()%100;
		it++;
		char *tmp = ft_utoa(nbr);
		str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : There is " + tmp + "%" + " love between " + user->getNickname() + " and " + *it + ".";
		free(tmp);
		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
	}
	else if ((*it).compare("!zodiac") == 0)
	{
		it++;
		if ((*it).compare("aries") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : If only you could convert all that stress into energy ! You'd be rich right now !";
		else if ((*it).compare("taurus") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : Stop spending all your money on food, you're already broke.";
		else if ((*it).compare("gemini") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : ";
		else if ((*it).compare("cancer") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : Stop being such a drama queen !";
		else if ((*it).compare("leo") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : I know you won't believe it, but you're NOT a Diva";
		else if ((*it).compare("virgo") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : Never seen such a control-freak ! You're scaring people !!";
		else if ((*it).compare("libra") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : If you like coffee then you are a Slytherin otherwise you're a Hufflepuff";
		else if ((*it).compare("scorpio") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : Did you know your parents had s*x on Valentine's day ?";
		else if ((*it).compare("sagittarius") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : ";
		else if ((*it).compare("capricorn") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : Only one present for your birthday AND christmas ??? What a childhood trauma ! You should talk about it.";
		else if ((*it).compare("aquarius") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : If you were wondering if you should leave sooner today - The answer is YES.";
		else if ((*it).compare("pisces") == 0)
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : Binge watching TVshows is NOT a goal in life you know ??";
		else 
			str = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName() + " : Please enter your sign after the command.";
		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
	}
	if("!help") 
	{
		
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

std::string const&	Server::getIpaddr(void) const
{
	return this->_ipaddr;
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

void	Server::setIpaddr(std::string ipaddr)
{
	this->_ipaddr = ipaddr;
}

/* ************************************************************************** */
