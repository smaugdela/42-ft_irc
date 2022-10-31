/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:04:06 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/28 14:49:38 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: LIST
//    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

//    The list command is used to list channels and their topics.  If the
//    <channel> parameter is used, only the status of that channel is
//    displayed.

//    If the <target> parameter is specified, the request is forwarded to
//    that server which will generate the reply.

//    Wildcards are allowed in the <target> parameter.

void list(Server *serv, Message &msg)
{
	std::string str;
	char *tmp = strdup(msg.getParams()[0].c_str());
	std::list<std::string> channels = split(tmp, ",");
	free(tmp);
	if ((msg.getParams().size() == 1) && msg.getParams()[0] != "")
	{
		for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			if (serv->getChannel(*it) != NULL)
			{
				str = *it;
				str += " ";
				str += serv->getChannel(*it)->getMembers().size();
			}
		}
	}
	else
		for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			if (serv->getChannel(*it) != NULL)
			{
				str = *it;
				str += " ";
				str += serv->getChannel(*it)->getMembers().size();
			}
		}
	str = RPL_LISTEND;
	str += "" + msg.getSender()->getNickname() + " :End of LIST.";
	msg.getSender()->send_to(str.c_str());
}
