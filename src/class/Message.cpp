/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:49 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/08 13:32:58 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Message::Message() : _sender(NULL), _message(NULL), _command(), _prefix(), _params()
{
}

Message::Message(Client *sender, std::string message) : _sender(sender), _message(message), _command(), _prefix(), _params()
{
}

Message::Message( const Message & src ) : _sender(src.getSender()), _message(src.getMessage()), _command(src.getCommand()), _prefix(src.getPrefix()), _params(src.getParams())
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

static std::string	capitalize(std::string const& low_str)
{
	std::string	upp_str(low_str);

	for (std::string::iterator it = upp_str.begin(); it != upp_str.end(); ++it)
		*it = toupper(*it);
	return upp_str;
}

bool	Message::parse_msg(void)
{
	const char *delim = " ";
	char*	tmp = strdup(_message.c_str());
	std::vector<std::string> 			tab_parse;
	std::vector<std::string>::iterator	str;

	char *token = strtok(tmp, delim);
	while(token != NULL)
	{
		tab_parse.push_back(std::string(token));
		token = strtok(NULL, delim);
	}
	free(tmp);

	if (tab_parse.size() < 1)
		return false;

	str = tab_parse.begin();
	if ((*str)[0] == ':')
	{
		setPrefix(*str);
		++str;
	}
	if (Check_command(*str))
	{
		setCommand(capitalize(*str));
	}
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
	if (str.size() == 0)
		return false;
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

std::string Message::getMessage(void) const
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