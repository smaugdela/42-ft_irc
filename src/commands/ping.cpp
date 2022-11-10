/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:10:15 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/10 14:23:11 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: PING
//    Parameters: <server1> [ <server2> ]

//    The PING command is used to test the presence of an active client or
//    server at the other end of the connection.  Servers send a PING
//    message at regular intervals if no other activity detected coming
//    from a connection.  If a connection fails to respond to a PING
//    message within a set amount of time, that connection is closed.  A
//    PING message MAY be sent even if the connection is active.

//    When a PING message is received, the appropriate PONG message MUST be
//    sent as reply to <server1> (server which sent the PING message out)
//    as soon as possible.  If the <server2> parameter is specified, it
//    represents the target of the ping, and the message gets forwarded
//    there.

void ping(Server *serv, Message &msg)
{
	if (serv == NULL)
		return ;

	std::string	str;

	if (msg.getParams().size() < 1)
	{
		str = ERR_NOORIGIN;
		str += " " + msg.getSender()->getNickname() + " :No origin specified";
		msg.getSender()->send_to(str);
	}
	else
	{
		Client *receiver = serv->getUser(msg.getParams()[0]);

		if (receiver == NULL)
		{
			str = ERR_NOSUCHSERVER;
			str += " " + msg.getSender()->getNickname() + " " + msg.getParams()[0] + " :No such server";
			receiver = msg.getSender();
		}
		else
			str = "PONG " + receiver->getNickname() + " :" + msg.getParams()[0];
		receiver->send_to(str);
	}
}
