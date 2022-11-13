/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:27:06 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/13 22:00:38 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: NICK
//    Parameters: <nickname>

//    NICK command is used to give user a nickname or change the existing
//    one.

static bool special_char(std::string to_check)
{
	int i = 0;
	while (to_check[i])
	{
		if (!isalnum(to_check[i]) && to_check[i] != '-' && to_check[i] != '_' && to_check[i] != '['
		&& to_check[i] != ']' && to_check[i] != '{' && to_check[i] != '}'
		&& to_check[i] != '\\' &&to_check[i] != '`' && to_check[i] != '|')
			return false;
		i++;	
	}
	return true;
}

void nick(Server *serv, Message &msg)
{
	if (serv == NULL)
		return ;

	std::string 	str;
	Client* const	client = msg.getSender();

	if (msg.getParams().size() > 1 || msg.getParams().size() == 0)
	{
		str = ERR_NONICKNAMEGIVEN;
		str += " :No nickname given";
	}
	else
	{
		std::string new_nick = msg.getParams()[0];
		if (new_nick.length() > 9 || new_nick.length() <= 0 || special_char(new_nick) == false)
		{
			str = ERR_ERRONEUSNICKNAME;
			str += " " + new_nick + " :Invalid nickname parameter(s).";
		}
		else if (serv->getUser(new_nick) != NULL)
		{
			str = ERR_NICKNAMEINUSE;
			str += " " + new_nick +  " " + new_nick + " :Nickname is already in use.";
		}
		else if (serv->getUser(new_nick) == NULL && special_char(new_nick) == true && client->getNickname().size() == 0)
		{
			str = "NICK ";
			str += new_nick;
			client->setNickname(new_nick);
			client->send_to(str);
			if (client->getAuthorize() && client->getNickname().size() && client->getUsername().size())
				client->welcome(serv);
			return ;
		}
		else if (serv->getUser(new_nick) == NULL && special_char(new_nick) == true && client->getNickname().size() != 0)
		{
			str = "NICK ";
			str += new_nick;
			std::map<std::string, Channel*>::const_iterator it;
			for (it = serv->getChans().begin(); it != serv->getChans().end(); ++it)
			{
				if (it->second->getMember(client->getNickname()) != NULL)
					it->second->broadcast(client, str);
			}
			client->send_to(str);
			client->setNickname(new_nick);
			return ;
		}
		client->send_to(str);
	}
}
