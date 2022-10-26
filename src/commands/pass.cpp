/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:12:17 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/26 11:06:20 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

void pass(Server *serv, Message &msg)
{
	std::string str;
	if (msg.getParams().size() < 1 && msg.getSender()->getAuthorize() == false)
	{
		str = ERR_NEEDMOREPARAMS;
		str +=  " PASS :Not enough parameters";
		msg.getSender()->setAuthorize(true);	// Necessary temporary authorization in order to send message;
		msg.getSender()->send_to(str);
		msg.getSender()->setAuthorize(false);
	}
	else if (msg.getParams().size() == 1)
	{
		if (msg.getSender()->getAuthorize())
		{
			str = ERR_ALREADYREGISTRED;
			str += ":Unauthorized command (already registered)";
			msg.getSender()->send_to(str);
		}
		else if (msg.getParams()[0] == serv->getPassword())
			msg.getSender()->setAuthorize(true);
	}
}
