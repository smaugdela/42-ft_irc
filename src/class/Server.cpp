/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/10 15:19:52 by smagdela         ###   ########.fr       */
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

void	Server::addUser(Client* new_user)
{
	if (new_user == NULL || _users.find(new_user->getFd()) != _users.end())
		return ;
	_users.insert(std::make_pair(new_user->getFd(), new_user));
}

void Server::rmUser(Client* user)
{
	if (user != NULL && _users.find(user->getFd()) != _users.end())
	{
		_users.erase(user->getFd());
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
	if (chan != NULL && _chans.find(chan->getName()) != _chans.end())
	{
		_chans.erase(_chans.find(chan->getName()));
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

void	Server::announceBot(Channel *channel, Client *user) const
{
	if (channel == NULL || user == NULL || _chans.find(channel->getName()) == _chans.end() || _users.find(user->getFd()) == _users.end())
		return ;

	std::string bot = BOTNAME;
	std::string	pref = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName();

	my_send(user, pref + " :Welcome to the channel " + channel->getName() + ". I am the " + bot + ". Use \"bot !help\" for more information...");
}

void Server::callbot(Channel *channel, Client *user, std::vector<std::string> const& params)
{
	if (channel == NULL || user == NULL || _chans.find(channel->getName()) == _chans.end() || _users.find(user->getFd()) == _users.end())
		return ;

	std::string bot = BOTNAME;
	std::string	pref = ":" + bot + "!" + bot + "@" + _config->getServerName() + " PRIVMSG " + channel->getName();
	std::string str;

	if (params.size() <= 2)
	{
		str = pref + " : Invalid request, " + user->getNickname() + ". Use \"bot !help\" for more informations.";
		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
		return ;
	}
	if (params[1] != ":bot")
		return ;
	else if (params[2][0] != '!')
	{
		str = pref + " : Invalid request, " + user->getNickname() + ". Use \"bot !help\" for more informations.";
		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
		return ;
	}

	if (params[2] == "!love" && params.size() == 4)
	{
		char *tmp = ft_utoa(rand() % 100);
		if (tmp == NULL)
		{
			*tmp = '0';
			str = pref + " : There is " + tmp + "%" + " love between " + user->getNickname() + " and " + params[3] + ".";
		}
		else
		{
			str = pref + " : There is " + tmp + "%" + " love between " + user->getNickname() + " and " + params[3] + ".";
			free(tmp);
		}

		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
	}
	else if (params[2] == "!zodiac" && params.size() == 4)
	{
		if (params[3] == "aries")
			str = pref + " : If only you could convert all that stress into energy ! You'd be rich right now !";
		else if (params[3] == "taurus")
			str = pref + " : Stop spending all your money on food, you're already broke.";
		else if (params[3] == "gemini")
			str = pref + " : Stop teasing everyone, you're not perfect either!";
		else if (params[3] == "cancer")
			str = pref + " : Stop being such a drama queen !";
		else if (params[3] == "leo")
			str = pref + " : I know you won't believe it, but you're NOT a Diva";
		else if (params[3] == "virgo")
			str = pref + " : Never seen such a control-freak ! You're scaring people !!";
		else if (params[3] == "libra")
			str = pref + " : If you like coffee then you are a Slytherin otherwise you're a Hufflepuff";
		else if (params[3] == "scorpio")
			str = pref + " : Did you know your parents had s*x on Valentine's day ?";
		else if (params[3] == "sagittarius")
			str = pref + " : Come back from the moon, the real life is on earth!";
		else if (params[3] == "capricorn")
			str = pref + " : Only one present for your birthday AND christmas ??? What a childhood trauma ! You should talk about it.";
		else if (params[3] == "aquarius")
			str = pref + " : If you were wondering if you should leave sooner today - The answer is YES.";
		else if (params[3] == "pisces")
			str = pref + " : Binge watching TVshows is NOT a goal in life you know ??";
		else 
			str = pref + " : Please enter your sign after the command.";
		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
	}
	else if (params[2] == "!fu" && params.size() == 3)
	{
		str = pref + " : That's not polite " + user->getNickname() + ".";
		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
	}
	else if (params[2] == "!help" && params.size() == 3)
	{
		str = pref + " : With this bot you can ask about your crush, your zodiac sign and more...";
		str += " For that, use the following command and enjoy! : \"bot !love <insert crush>\", \"bot !zodiac <insert sign>\", \"bot !fu\".";
		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
	}
	else
	{
		str = pref + " : Invalid request, " + user->getNickname() + ". Use \"bot !help\" for more informations.";
		std::map<sockfd, Client *>::const_iterator it2;
		for (it2 = channel->getMembers().begin(); it2 != channel->getMembers().end(); ++it2)
			my_send(it2->second, str);
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
