/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:01:46 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/28 12:30:25 by smagdela         ###   ########.fr       */
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
		return ;
	}
	char *tmp = strdup(msg.getParams()[0].c_str());
	std::list<std::string> channels = split(tmp, ",");
	free(tmp);
	for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (serv->getChannel(*it) == NULL)
		{
			str = ERR_NOSUCHCHANNEL;
			str += " " + *it + " :No such channel";
			msg.getSender()->send_to(str);
		}
	}
	if (msg.getParams().size() == 1 && msg.getParams()[0] == "0")
	{
		for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			if (serv->getChannel(*it)->getMember(msg.getSender()->getNickname()) != NULL)
			{
				serv->getChannel(*it)->kickMember(msg.getSender());
				serv->getChannel(*it)->broadcast("PART " + *it + " :Left all channels");
			}
		}
	}
	else
	{
		for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			if ((*it)[0] != '#' && (*it)[0] != '&' && (*it)[0] != '+' && (*it)[0] != '!')
				it->insert(it->begin(), '#');
			it->resize(50);
			serv->addChan(new Channel(*it));
			serv->getChannel(*it)->addMember(msg.getSender());
			serv->getChannel(*it)->broadcast("JOIN " + *it)
			// Add rpl_topic and rpl_namereply to autheticate the user on this channel.
		}
	}
}
