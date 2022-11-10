/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:04:06 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/10 14:31:47 by smagdela         ###   ########.fr       */
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
	if (serv == NULL)
		return ;

	std::string str;

	if (msg.getParams().size() == 0)
	{
		for (std::map<std::string, Channel*>::const_iterator it = serv->getChans().begin(); it != serv->getChans().end(); ++it)
		{
			str = RPL_LIST;
			char *tmp = ft_utoa(it->second->getMembers().size());
			if (tmp != NULL)
			{
				str += " " + msg.getSender()->getNickname() + " " + it->second->getName() + " " + tmp;
				free(tmp);
			}
			else
				str += " " + msg.getSender()->getNickname() + " " + it->second->getName() + " ?";
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

				char *tmp = ft_utoa(serv->getChannel(*it)->getMembers().size());
				if (tmp != NULL)
				{
					str += " " + msg.getSender()->getNickname() + " " + *it + " " + tmp;
					free(tmp);
				}
				else
					str += " " + msg.getSender()->getNickname() + " " + *it + " ?";

				msg.getSender()->send_to(str);
			}
		}
	}
	str = RPL_LISTEND;
	str += " " + msg.getSender()->getNickname() + " :End of LIST.";
	msg.getSender()->send_to(str);
}
