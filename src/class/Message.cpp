/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:49 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/21 17:22:19 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Message::Message() : _sender(NULL), _receiver(NULL), _message(NULL), _command(), _prefix(), _params()
{
}

Message::Message(Client *sender, Client *receiver, char *message) : _sender(sender), _receiver(receiver), _message(message), _command(), _prefix(), _params()
{
}

Message::Message( const Message & src ) : _sender(src.getSender()), _receiver(src.getReceiver()), _message(src.getMessage()), _command(src.getCommand()), _prefix(src.getPrefix()), _params(src.getParams())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Message::~Message()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Message &				Message::operator=( Message const & rhs )
{
	if ( this != &rhs )
	{
		this->_sender = rhs.getSender();
		this->_receiver = rhs.getReceiver();
		this->_message = rhs.getMessage();
		this->_command = rhs.getCommand();
		this->_prefix = rhs.getPrefix();
		this->_params = rhs.getParams();
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Message const & i )
{
	o << "Prefix: [" << i.getPrefix() << "]\nCommand: [" << i.getCommand() << "]\nParameters: [";
	for (std::vector<std::string>::const_iterator it = i.getParams().begin(); it != i.getParams().end(); ++it)
		o << *it << "] [";
	o << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool	Message::parse_msg(void)
{
	const char *delim = " ";
	std::vector<std::string> 			tab_parse;
	std::vector<std::string>::iterator	str;

	char *token = strtok(_message, delim);
	while(token != NULL)
	{
		tab_parse.push_back(std::string(token));
		token = strtok(NULL, delim);
	}

	if (tab_parse.size() < 1)
		return false;

	str = tab_parse.begin();
	if ((*str)[0] == ':')
	{
		setPrefix(*str);
		++str;
	}
	if (Check_command(*str))
		setCommand(*str);
	else
	{
		std::cout << "Invalid command format." << std::endl;
		return false;
	}
	++str;
	if (str != tab_parse.end())
	{
		tab_parse.erase(tab_parse.begin(), str);
		setParams(tab_parse);
	}
	return true;
}

bool Message::Check_command(std::string str)
{
	if (str.size() == 3 && isdigit(str[0]) == true)
	{
		for(int i = 0; i < 3; i++)
		{
			if (isdigit(str[i]) == false)
				return false;
		}
		return true;
	}
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isalpha(str[i]) == 0)
			return false;
	}
	return true;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

char *Message::getMessage(void) const
{
	return (this->_message);
}

std::string const& Message::getCommand(void) const
{
	return (this->_command);
}

std::string const& Message::getPrefix(void) const
{
	return (this->_prefix);
}

std::vector<std::string> const& Message::getParams(void) const
{
	return (this->_params);
}

Client*	Message::getSender(void) const
{
	return this->_sender;
}

Client*	Message::getReceiver(void) const
{
	return this->_receiver;
}

void Message::setCommand(std::string command)
{
	this->_command = command;
}

void Message::setPrefix(std::string prefix)
{
	this->_prefix = prefix;
}

void Message::setParams(std::vector<std::string> params)
{
	this->_params= params;
}

/* ************************************************************************** */