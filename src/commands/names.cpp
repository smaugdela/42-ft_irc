/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:19:43 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/07 18:42:24 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/*  Command: NAMES
    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

    By using the NAMES command, a user can list all nicknames that are
    visible to him. For more details on what is visible and what is not,
    see "Internet Relay Chat: Channel Management" [IRC-CHAN].  
    The <channel> parameter specifies which channel(s) to return information
    about.  There is no error reply for bad channel names.
    If no <channel> parameter is given, a list of all channels and their
    occupants is returned.  At the end of this list, a list of users who
    are visible but either not on any channel or not on a visible channel
    are listed as being on `channel' "*".
    If the <target> parameter is specified, the request is forwarded to
    that server which will generate the reply.
    Wildcards are allowed in the <target> parameter.
    Numerics:
            ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
            RPL_NAMREPLY                    RPL_ENDOFNAMES
*/

// Check for '@' addition in the packet for the first member.
void names(Server *serv, Message &msg)
{
    std::string str;

    if (msg.getParams().size() == 0)
    {
        std::map<std::string, Channel*> chans = serv->getChans();
        std::map<std::string, Channel*>::iterator it = chans.begin();
        for(; it != chans.end(); it++)
        {
            std::map<sockfd, Client*> members = serv->getChannel(it->first)->getMembers();
            std::map<sockfd, Client*>::iterator it2 = members.begin();
            str = RPL_NAMREPLY;
            str += " " + msg.getSender()->getNickname() + " =" + it->first + " :";
            for (; it2 != members.end(); it2++)
                str += it2->second->getNickname() + " ";
            msg.getSender()->send_to(str);
			str = RPL_ENDOFNAMES;
			str += " " + msg.getSender()->getNickname() + " ";
			str += it->first + ":End of /NAMES list";
			msg.getSender()->send_to(str);
        }
    }
    else
    {
        char *tmp = strdup(msg.getParams()[0].c_str());
        std::list<std::string> channels = split(tmp, ",");
        free(tmp);

	    for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
        {
            if (serv->getChannel(*it) != NULL)
            {
	            std::map<sockfd, Client*> members = serv->getChannel(*it)->getMembers();
                std::map<sockfd, Client*>::iterator it2 = members.begin();
                str = RPL_NAMREPLY;
                str += " " + msg.getSender()->getNickname() + " = " + *it + " :";
                for (; it2 != members.end(); it2++)
				{
					if (it2->second->getMode().find('i') == std::string::npos || it2->second == msg.getSender())
					{
						if (it2->second == serv->getChannel(*it)->getCreator())
							str += "@";
	                    str += it2->second->getNickname() + " ";
					}
				}
				msg.getSender()->send_to(str);
				str = RPL_ENDOFNAMES;
				str += " " + msg.getSender()->getNickname() + " ";
				str += *it + " :End of /NAMES list";
				msg.getSender()->send_to(str);
            }
        }
    }
}
