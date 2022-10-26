/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:27:06 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/26 11:44:47 by smagdela         ###   ########.fr       */
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
	std::string 	str;
	Client* const	client = msg.getSender();

	if ((msg.getParams().size() > 1))
	{
		str = ERR_NONICKNAMEGIVEN;
		str += " :Invalid nickname parameter(s).";
	}
	else
	{
		std::string new_nick = msg.getParams()[0];
		if (new_nick.length() > 9 || special_char(new_nick) == false)
		{
			str = ERR_ERRONEUSNICKNAME;
			str += " " + new_nick + " :Invalid nickname parameter(s).";
		}
		if (serv->getUser(new_nick) == NULL && special_char(new_nick) == true)
		{
			msg.getSender()->setNickname(new_nick);
			str = "NICK ";
			str += new_nick;
		}
		else if (serv->getUser(new_nick) != NULL)
		{
			str = ERR_NICKNAMEINUSE;
			str += " " + new_nick;
			str +=  " :Nickname is already in use.";
		}
	}
	msg.getSender()->send_to(str.c_str());

	if (client->getAuthorize() && client->getNickname().size() && client->getUsername().size())
		client->welcome(serv);
}
