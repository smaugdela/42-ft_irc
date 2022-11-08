/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:01:46 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/08 13:41:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

// 		Command: JOIN
//		Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0"
// 	  The JOIN command is used by a user to request to start listening to
//    the specific channel.  Servers MUST be able to parse arguments in the
//    form of a list of target, but SHOULD NOT use lists when sending JOIN
//    messages to clients.

//    Once a user has joined a channel, he receives information about
//    all commands his server receives affecting the channel.  This
//    includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
//    This allows channel members to keep track of the other channel
//    members, as well as channel modes.

//    If a JOIN is successful, the user receives a JOIN message as
//    confirmation and is then sent the channel's topic (using RPL_TOPIC) and
//    the list of users who are on the channel (using RPL_NAMREPLY), which
//    MUST include the user joining.

//    Note that this message accepts a special argument ("0"), which is
//    a special request to leave all channels the user is currently a member
//    of.  The server will process this message as if the user had sent
//    a PART command (See Section 3.2.2) for each channel he is a member
//    of.
//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//            ERR_CHANNELISFULL               ERR_BADCHANMASK
//            ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//            ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
//            RPL_TOPIC

void join(Server *serv, Message &msg)
{
	std::string str;

	if (msg.getParams().size() < 1)
	{
		str = ERR_NEEDMOREPARAMS;
		str += " " + msg.getSender()->getNickname() + " :Error need more params.";
		msg.getSender()->send_to(str);
	}
	// else if (msg.getParams().size() == 1 && msg.getParams()[0] == "#0")
	// {
	// 	for (std::map<std::string, Channel*>::const_iterator it = serv->getChans().begin(); it != serv->getChans().end(); ++it)
	// 	{
	// 		if (it->second->getMember(msg.getSender()->getNickname()) != NULL)
	// 		{
	// 			it->second->broadcast(msg.getSender(), "PART " + msg.getSender()->getNickname() + " :Left all channels");
	// 			it->second->kickMember(msg.getSender());
	// 		}
	// 	}
	// }
	else
	{
		char *tmp = strdup(msg.getParams()[0].c_str());
		std::list<std::string> channels = split(tmp, ",");
		free(tmp);

		for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			if ((*it)[0] != '#' && (*it)[0] != '&' && (*it)[0] != '+' && (*it)[0] != '!')
				it->insert(it->begin(), '#');
			if (it->size() > 50)
				it->resize(50);
			if (serv->getChannel(*it) == NULL)
				serv->addChan(new Channel(*it, msg.getSender()));
			serv->getChannel(*it)->addMember(msg.getSender());
			
			Message names_msg(msg.getSender(), "NAMES " + *it);
			names_msg.parse_msg();
			names(serv, names_msg);

			msg.getSender()->send_to("JOIN " + *it);
			serv->getChannel(*it)->broadcast(msg.getSender(), "JOIN " + *it);
		}
	}
}
