/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:49 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/17 17:32:46 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Message::Message()
{
}

Message::Message(Client *sender, Client *receiver, std::string message) : _sender(sender), _receiver(receiver), _message(message)
{
	const char *delim = " ";
	std::vector<std::string> tab_parse;
	
	char *token = strtok(const_cast<char*>(_message.c_str()), delim);
	while(token != NULL)
	{
		tab_parse.push_back(std::string(token));
		token = strtok(NULL, delim);
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


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string const& Message::getMessage(void) const
{
	return (this->_message);
}

/* ************************************************************************** */