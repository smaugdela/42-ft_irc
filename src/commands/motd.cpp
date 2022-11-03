/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:24:21 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/03 11:48:48 by fboumell         ###   ########.fr       */
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
	std::string					str;
	std::vector<std::string>	ret;
	

	if (msg.getParams().size() > 1)
	{
		str = ERR_NOMOTD;
		str += " " + msg.getSender()->getNickname() + " :Invalid Motd parameter(s).";
	}
	else
	{
		std::ifstream	ifs("./src/config/motd.txt", std::ifstream::in);
		if (ifs.good())
		{
			str = RPL_MOTDSTART;
			str += " " + msg.getSender()->getNickname() + " :- ";
			str += serv->getConfig()->getServerName() + " ";
			str += "Message of the day - ";
			msg.getSender()->send_to(str.c_str());
			
			std::string	line;
			while (getline(ifs, line))
				ret.push_back(line);
			for (std::vector<std::string>::iterator it = ret.begin(); it != ret.end(); it++)
			{
				str = RPL_MOTD;
				str += " " + msg.getSender()->getNickname() + " ";
				str += *it;
				msg.getSender()->send_to(str.c_str());
			}
		}
		else
		{
			str = ERR_NOMOTD;
			str += " " + msg.getSender()->getNickname() + " ";
			str += ":MOTD File is missing";
			msg.getSender()->send_to(str.c_str());
 		}	
		ifs.close();
		
		str = RPL_ENDOFMOTD;
		str += " " + msg.getSender()->getNickname() + " ";
		str += ":End of /MOTD command";
	}
	msg.getSender()->send_to(str.c_str());
}
