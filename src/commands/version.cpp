/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/10 14:23:30 by smagdela         ###   ########.fr       */
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
	if (serv == NULL)
		return ;

	std::string       str;

	if (msg.getParams().size() > 1)
	{
		str = ERR_NOSUCHSERVER;
		str += " " + msg.getSender()->getNickname() + "  :Invalid Version parameter(s)."; 
	}
	else
	{
		str = RPL_VERSION;
		str += " " + msg.getSender()->getNickname() + " Version: ";
		str += serv->getConfig()->getServerVersion();
	}
	msg.getSender()->send_to(str.c_str());
}
