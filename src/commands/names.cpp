/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:19:43 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/01 14:53:50 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/*  Command: NAMES
    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

    By using the NAMES command, a user can list all nicknames that are
    visible to him. For more details on what is visible and what is not,
    see "Internet Relay Chat: Channel Management" [IRC-CHAN].  The
    <channel> parameter specifies which channel(s) to return information
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


void names(Server *serv, Message &msg)
{
    std::string str;
    (void)serv;
    (void)msg;

    // if (msg.getParams().size() == 0)
    // {
    //     std::map<std::string, Channel*> chans = serv->getChans();
    //     std::map<std::string, Channel*>::iterator it = chans.begin();
    //     for(; it != chans.end(); it++)
    //     {
    //         std::map<sockfd, Client*> members = serv->getChannel(*it)->getMembers();
    //         std::map<sockfd, Client*>::iterator it2 = members.begin();
    //         for (; it2 != members.end(); it2++)
    //         {
                
    //         }
    //     }
    // }
}
