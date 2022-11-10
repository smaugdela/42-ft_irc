/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallops.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:22:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/10 14:23:39 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

void wallops(Server *serv, Message &msg)
{
	if (serv == NULL)
		return ;

	std::string	str;

	if (msg.getParams().size() < 1)
	{
		str = ERR_NEEDMOREPARAMS;
		str += " " + msg.getSender()->getNickname() + ":Error need more params.";
		msg.getSender()->send_to(str);
	}
	else if (msg.getSender()->getMode().find('o') != std::string::npos)
	{
		size_t start = msg.getMessage().find(':', msg.getPrefix().size() + msg.getCommand().size());
		std::string	text = "";
		if (start != std::string::npos)
			text = msg.getMessage().substr(start);
		
		str = msg.getSender()->getPrefix() + " WALLOPS " + text;

		std::map<sockfd, Client *>::const_iterator it;
		for (it = serv->getUsers().begin(); it != serv->getUsers().end(); ++it)
		{
			if (it->second->getMode().find('w') != std::string::npos)
				my_send(it->second, str);
		}
	}
}
