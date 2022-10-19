/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:49 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/19 17:12:17 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Message::Message()
{
}

Message::Message(Client *sender, Client *receiver, char *message) : _sender(sender), _receiver(receiver), _message(message)
{
	// char delim = ' ';
	// std::stringstream ss(_message);
	// std::string token;
	// while (getline(ss, token, delim))
	// {
	// 	tab_parse.push_back(token);
	// }
	
	const char *delim = " ";
	std::vector<std::string> tab_parse;
	
	char *token = strtok(_message, delim);
	while(token != NULL)
	{
		tab_parse.push_back(std::string(token));
		token = strtok(NULL, delim);
	}

	std::vector<std::string>::iterator it = tab_parse.begin();
	for (; it != tab_parse.end(); it++)
	{	
		std::string str = *it;
		if (str[0] == ':')
		{
			if (Check_prefix(str) == true)
				setPrefix(str);
		}
		else
		{
			if (Check_command(str) == true)
				setCommand(str);
			else
				setParams(str);
		}
		it++;
	}
}

Message::Message( const Message & src )
{
	(void)src;
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
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	(void)rhs;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Message const & i )
{
	o << "Raw message: " << i.getMessage();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

bool Message::Check_prefix(std::string str)
{
	(void)str;
	return false;
}

bool Message::Check_command(std::string str)
{
	if (str.size() == 3 && isdigit(str[0]) == true)
	{
		for(int i = 0; i < 3; i++)
			if (isdigit(str[i]) == false)
				return false;
		return true;
	}
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isalpha(str[i]) == false)
			return false;
		return true;
	}
	return false;
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

std::string const& Message::getParams(void) const
{
	return (this->_params);
}

void Message::setCommand(std::string command)
{
	this->_command = command;
}

void Message::setPrefix(std::string prefix)
{
	this->_prefix = prefix;
}

void Message::setParams(std::string params)
{
	this->_params= params;
}

/* ************************************************************************** */