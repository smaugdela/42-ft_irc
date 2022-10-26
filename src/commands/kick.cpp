/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:12:03 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/26 13:37:14 by fboumell         ###   ########.fr       */
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
	(void)serv;
	std::string str;
	(void)serv;

	if ((msg.getParams().size() == 0))
	{
		str = ERR_NEEDMOREPARAMS;
		str += " :Error need more params.";
	}
	if (msg.getSender()->getAdm() == false)
	{
		str = ERR_CHANOPRIVSNEEDED;
		str += "chan name";
		str += " :You're not channel operator";
	}
	msg.getSender()->send_to(str.c_str());
}
