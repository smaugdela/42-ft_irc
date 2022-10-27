/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/27 14:59:41 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/* Command: VERSION
   Parameters: [ <target> ]

   The VERSION command is used to query the version of the server
   program. An optional parameter <target> is used to query the version
   of the server program which a client is not directly connected to.
   Wildcards are allowed in the <target> parameter.
   Numeric Replies:
	   ERR_NOSUCHSERVER                RPL_VERSION */
	   
	   
void version(Server *serv, Message &msg)
{
	std::string       str;

	if (msg.getParams().size() > 1)
	{
		str = ERR_NOSUCHSERVER;
		str += " " + msg.getSender()->getNickname() + "  :Invalid Version parameter(s)."; 
	}
	else
	{
		str = RPL_VERSION;
		str += " " + msg.getSender()->getNickname() + " Version of TheCatServer: ";
		str += serv->getConfig()->getServerVersion();
	}
	msg.getSender()->send_to(str.c_str());
}
