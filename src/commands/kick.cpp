/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:12:03 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/26 17:55:51 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

// La commande /kick te permet de virer quelqu'un du channel. !! OPerator Only !! 
// 	 Command: KICK
//    Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
//                [<comment>]

//    The KICK command can be used to request the forced removal of a user
//    from a channel.  It causes the <user> to PART from the <channel> by
//    force.  For the message to be syntactically correct, there MUST be
//    either one channel parameter and multiple user parameter, or as many
//    channel parameters as there are user parameters.  If a "comment" is
//    given, this will be sent instead of the default message, the nickname
//    of the user issuing the KICK.

//    The server MUST NOT send KICK messages with multiple channels or
//    users to clients.  This is necessarily to maintain backward
//    compatibility with old client software.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//            ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
//            ERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL

void kick(Server *serv, Message &msg)
{
	std::string str;

	if ((msg.getParams().size() == 0))
	{
			str = ERR_NEEDMOREPARAMS;
			str += " :Error need more params.";
	}
	else
	{
			char *tmp = strdup(msg.getParams()[0].c_str());
			std::list<std::string> channels = split(tmp, ",");
			free(tmp);
			tmp = strdup(msg.getParams()[1].c_str());
			std::list<std::string> users = split(tmp, ",");
			free(tmp);
			for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
			{
				if (!serv->getChannel(*it))
				{
						str =  ERR_NOSUCHCHANNEL;
						str += " ";
						str += *it;
						str += ": No such channel.";
						msg.getSender()->send_to(str.c_str());

				}
				if (msg.getSender()->getAdm() == false) // verifier dans le channel
				{
						str = ERR_CHANOPRIVSNEEDED;
						str += *it;
						str += " :You're not channel operator";
						msg.getSender()->send_to(str.c_str());

				}
				for (std::list<std::string>::iterator it2 = users.begin(); it2 != users.end(); ++it2)
				{
					if (!serv->getUser(*it))
					{
						str = ERR_USERNOTINCHANNEL;
						str += " ";
						str += *it2 + *it;
						str += " :They aren't on that channel.";
						msg.getSender()->send_to(str.c_str());
					}
					else 
					{
						str = "KICK " + *it + " " + *it2 + " :" + msg.getParams()[2];
						std::map<sockfd, Client*> tmp2 = serv->getChannel(*it)->getMembers();
						tmp2.erase(tmp2.find(serv->getUser(*it2)->getFd()));
					}
				}
			}
	}
	msg.getSender()->send_to(str.c_str());
}
