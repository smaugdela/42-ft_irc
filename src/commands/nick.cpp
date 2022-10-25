/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:27:06 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/25 10:53:11 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: NICK
//    Parameters: <nickname>

//    NICK command is used to give user a nickname or change the existing
//    one.

void nick(Server *serv, Message &msg)
{
	std::string str;

	if ((msg.getParams().size() > 1) || msg.getParams().size() > 9)
	{
		str = ERR_NONICKNAMEGIVEN;
		str += " :Invalid nickname parameter(s).";
	}
	else
	{
		std::string new_nick = msg.getParams()[0];
		if (serv->getUser(new_nick) == NULL)
		{
			msg.getSender()->setNickname(new_nick);
			str = "NICK ";
			str += new_nick;
		}
		else if (serv->getUser(new_nick) != NULL)
		{
			str = ERR_NICKNAMEINUSE;
			str +=  " :Nickname is already in use.";
		}
	}
	my_send(msg.getSender(), str.c_str());
}
