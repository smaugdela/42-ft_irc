/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:27:44 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/04 18:16:12 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//   Command: QUIT
//    Parameters: [ <Quit Message> ]

//    A client session is terminated with a quit message.  The server
//    acknowledges this by sending an ERROR message to the client.

void quit(Server *serv, Message &msg)
{
	std::string	str = "QUIT";

	for (size_t i = 0; i < msg.getParams().size(); ++i)
		str += " " + msg.getParams()[i];
	if (msg.getParams().size() == 0)
		str += " :Client quit";

	msg.getSender()->send_to(str);
	
	std::map<std::string, Channel*>::const_iterator it;
	for (it = serv->getChans().begin(); it != serv->getChans().end(); ++it)
	{
		if (it->second->getMember(msg.getSender()->getNickname()) != NULL)
			it->second->broadcast(msg.getSender(), str);
	}

	serv->rmUser(msg.getSender());
}
