/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:27:44 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/26 12:18:39 by smagdela         ###   ########.fr       */
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

	for (size_t i =0; i < msg.getParams().size(); ++i)
		str += " " + msg.getParams()[i];
	if (msg.getParams().size() == 0)
		str += " :Client quit";
	msg.getSender()->send_to(str);
	serv->rmUser(msg.getSender());
}
