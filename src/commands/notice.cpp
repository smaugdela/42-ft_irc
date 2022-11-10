/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:35:24 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/10 14:22:48 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

void notice(Server *serv, Message &msg)
{
	if (serv == NULL)
		return ;

	std::string str;

	if (msg.getParams().size() < 2)
		return ;
	else if (msg.getParams()[0].find_first_of("#&+!") != 0 && serv->getUser(msg.getParams()[0]) == NULL)
		return ;
	else if (msg.getParams()[0].find_first_of("#&+!") == 0 && serv->getChannel(msg.getParams()[0]) == NULL)
		return ;
	else
	{
		size_t start = msg.getMessage().find(':', msg.getPrefix().size() + msg.getCommand().size() + msg.getParams()[0].size());
		std::string	text = "";
		if (start != std::string::npos)
			text = msg.getMessage().substr(start);

		if (msg.getParams()[0].find_first_of("#&+!") == 0)
			serv->getChannel(msg.getParams()[0])->broadcast(msg.getSender(), "NOTICE " + msg.getParams()[0] + " " + text);
		else
			my_send(serv->getUser(msg.getParams()[0]), msg.getSender()->getPrefix() + " NOTICE " + msg.getParams()[0] + " " + text);
	}
}
