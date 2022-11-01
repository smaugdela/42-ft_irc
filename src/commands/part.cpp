/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:30:34 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/01 15:03:09 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/*
	Command: PART
	Parameters: <channel> *( "," <channel> ) [ <Part Message> ]

	The PART command causes the user sending the message to be removed
	from the list of active members for all given channels listed in the
	parameter string.  If a "Part Message" is given, this will be sent
	instead of the default message, the nickname.  This request is always
	granted by the server.
	Servers MUST be able to parse arguments in the form of a list of
	target, but SHOULD NOT use lists when sending PART messages to
	clients.
	Numeric Replies:
			ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
			ERR_NOTONCHANNEL
*/

		   
void part(Server *serv, Message &msg)
{
	std::string	str;
	
	if (msg.getParams().size() == 0)
	{
		str = ERR_NEEDMOREPARAMS;
		str += " " + msg.getSender()->getNickname() + " ";
		str += ":Error need more params.";
	}
	else
	{
		char *tmp = strdup(msg.getParams()[0].c_str());
		std::list<std::string> channels = split(tmp, ",");
		free(tmp);
		for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
		{
			if (!serv->getChannel(*it))
			{
				str = ERR_NOSUCHCHANNEL;
				str += " " + msg.getSender()->getNickname() + " ";
				str += *it + " :No such channel";
				msg.getSender()->send_to(str.c_str());
			}
			else if (!serv->getChannel(*it)->getMember(msg.getSender()->getNickname()))
			{
				str = ERR_NOTONCHANNEL;
				str += " " + msg.getSender()->getNickname() + " ";
				str += *it + " " + ":You're not on that channel";
				msg.getSender()->send_to(str.c_str());
			}
			else
			{
				str = "PART " + *it + " " + msg.getParams()[1];
				msg.getSender()->send_to(str.c_str());
				std::map<sockfd, Client*> tmp2 = serv->getChannel(*it)->getMembers();
				tmp2.erase(tmp2.find(serv->getUser(msg.getSender()->getNickname())->getFd()));
			}
		}
	}
	msg.getSender()->send_to(str.c_str());
}
