/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:24:21 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/26 17:57:41 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/*	Command: MOTD
	Parameters: [ <target> ]

	The MOTD command is used to get the "Message Of The Day" of the given
	server, or current server if <target> is omitted.
	Wildcards are allowed in the <target> parameter.
	Numeric Replies:
			RPL_MOTDSTART                   RPL_MOTD
			RPL_ENDOFMOTD                   ERR_NOMOTD */


void motd(Server *serv, Message &msg)
{
	std::string	str;

	if (msg.getParams().size() > 1)
	{
		str = ERR_NOMOTD;
		str += " " + msg.getSender()->getNickname() + " :Invalid nickname parameter(s).";
	}
	else
	{
		(void)serv;		
	}
	msg.getSender()->send_to(str.c_str());
}
