/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:38:00 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/03 16:56:55 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//     Command: PRIVMSG
//    Parameters: <msgtarget> <text to be sent>

//    PRIVMSG is used to send private messages between users, as well as to
//    send messages to channels.  <msgtarget> is usually the nickname of
//    the recipient of the message, or a channel name.

//    The <msgtarget> parameter may also be a host mask (#<mask>) or server
//    mask ($<mask>).  In both cases the server will only send the PRIVMSG
//    to those who have a server or host matching the mask.  The mask MUST
//    have at least 1 (one) "." in it and no wildcards following the last
//    ".".  This requirement exists to prevent people sending messages to
//    "#*" or "$*", which would broadcast to all users.  Wildcards are the
//    '*' and '?'  characters.  This extension to the PRIVMSG command is
//    only available to operators.

//    Numeric Replies:

//            ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
//            ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
//            ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
//            ERR_NOSUCHNICK
//            RPL_AWAY

void privmsg(Server *serv, Message &msg)
{
	std::string	str;

	if (msg.getParams().size() == 0)
	{
		str = ERR_NORECIPIENT;
		str += " " + msg.getSender()->getNickname() + " :No recipient given PRIVMSG";
	}
	else if (msg.getParams().size() == 1)
	{
		str = ERR_NOTEXTTOSEND;
		str += " " + msg.getSender()->getNickname() + " :No text to send";
	}
	else if (msg.getParams()[0].find_first_of("#&+!") != 0 && serv->getUser(msg.getParams()[0]) == NULL)
	{
		str = ERR_NOSUCHNICK;
		str += " " + msg.getSender()->getNickname() + " " + msg.getParams()[0] + " :No such nick/channel";
	}
	else if (msg.getParams()[0].find_first_of("#&+!") == 0 && serv->getChannel(msg.getParams()[0]) == NULL)
	{
		str = ERR_NOSUCHNICK;
		str += " " + msg.getSender()->getNickname() + " " + msg.getParams()[0] + " :No such nick/channel";
	}
	else
	{
		size_t start = msg.getMessage().find(':', msg.getPrefix().size() + msg.getCommand().size() + msg.getParams()[0].size());
		std::string	text(msg.getMessage().substr(start));

		if (msg.getParams()[0].find_first_of("#&+!") == 0)
		{
			serv->getChannel(msg.getParams()[0])->broadcast(msg.getSender(), "PRIVMSG " + msg.getParams()[0] + " " + text);
			return ;
		}
		else
		{
			my_send(serv->getUser(msg.getParams()[0]), msg.getSender()->getPrefix() + " PRIVMSG " + msg.getParams()[0] + " " + text);
			return ;
		}
	}
	msg.getSender()->send_to(str);
}
