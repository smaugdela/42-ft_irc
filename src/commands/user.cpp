/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:15:22 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/14 11:49:08 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: USER
//    Parameters: <user> <mode> <unused> <realname>

//    The USER command is used at the beginning of connection to specify
//    the username, hostname and realname of a new user.

//    The <mode> parameter should be a numeric, and can be used to
//    automatically set user modes when registering with the server.  This
//    parameter is a bitmask, with only 2 bits having any signification: if
//    the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
//    set, the user mode 'i' will be set.  (See Section 3.1.5 "User
//    Modes").

//    The <realname> may contain space characters.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

void user(Server *serv, Message &msg)
{
	if (serv == NULL)
		return ;

	std::string 	str;
	Client* const	client = msg.getSender();

	if (msg.getParams().size() < 4)
	{
		str = ERR_NEEDMOREPARAMS;
		str += "USER ";
		if (client->getNickname().size())
			str += client->getNickname();
		else
			str += "*";
		str += " :Not enough parameters";
		client->send_to(str);
	}
	else if (client->getUsername().size())
	{
		str = ERR_ALREADYREGISTRED;
		if (client->getNickname().size())
			str += client->getNickname();
		else
			str += "*";
		str += " :Unauthorized command (already registered)";
		client->send_to(str);
	}
	else if (msg.getParams().size() >= 4)
	{
		std::vector<std::string>::const_iterator it = msg.getParams().begin();
		client->setUsername(*it);
		std::string realname;
		if ((*it)[0] == ':')
			realname =it->substr(1);
		else
			realname = *it;
		for (; it != msg.getParams().end(); ++it)
			realname += " " + *it;
		client->setRealname(realname);
		if (client->getAuthorize() && client->getNickname().size() && client->getUsername().size())
			client->welcome(serv);
	}
}
