/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:06:15 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/03 14:29:45 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel()
{
}

Channel::Channel(std::string name) : _name(name), _topic(), _members()
{
}

Channel::Channel( const Channel & src )
{
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Channel &				Channel::operator=( Channel const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	(void)rhs;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Channel const & i )
{
	o << "Channel name: " << i.getName();
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
Will send to all the members of this channel a message from Client 'sender' with the correct prefix,
except himself (as he does not need to receive its own messages).
*/
void	Channel::broadcast(Client *sender, std::string msg_str) const
{
	if (sender == NULL)
		return ;

	std::map<sockfd, Client*>::const_iterator it;
	msg_str = sender->getPrefix() + " " + msg_str;

	for (it = _members.begin(); it != _members.end(); ++it)
	{
		if (it->second != sender)
			my_send(it->second, msg_str);
	}
}

Client *Channel::getMember(std::string member) const
{
	std::map<sockfd, Client*>::const_iterator	it;

	for (it = _members.begin(); it != _members.end(); ++it)
	{
		if (it->second->getNickname() == member)
			break ;
	}
	if (it == _members.end())
		return NULL;
	return it->second;
}

void	Channel::addMember(Client *member)
{
	_members.insert(std::make_pair(member->getFd(), member));
}

void	Channel::kickMember(Client *member)
{
	if (member != NULL)
	{
		_members.erase(member->getFd());
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string const& Channel::getName(void) const
{
	return (this->_name);
}

std::map<sockfd, Client*> const&	Channel::getMembers(void)
{
 	return (this->_members);
}

std::string	const&	Channel::getTopic(void) const
{
	return (this->_topic);
}

void	Channel::setTopic(std::string topic)
{
	_topic = topic;
}

/* ************************************************************************** */
