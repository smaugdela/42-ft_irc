/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:04:06 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/03 14:57:54 by ajearuth         ###   ########.fr       */
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
	if (msg.getParams().size() == 0)
	{
		for (std::map<std::string, Channel*>::const_iterator it = serv->getChans().begin(); it != serv->getChans().end(); ++it)
		{
			str = RPL_LIST;
			str += " " + it->second->getName() + " " + std::to_string(it->second->getMembers().size());
			msg.getSender()->send_to(str);
		}
	}
	else
	{
		char *tmp = strdup(msg.getParams()[0].c_str());
		std::list<std::string> channels = split(tmp, ",");
		free(tmp);
		for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			if (serv->getChannel(*it) != NULL)
			{
				str = RPL_LIST;
				str += " " + *it;
				str += " " + std::to_string(serv->getChannel(*it)->getMembers().size());
			}
		}
	}
	str = RPL_LISTEND;
	str += "" + msg.getSender()->getNickname() + " :End of LIST.";
	msg.getSender()->send_to(str);
}
