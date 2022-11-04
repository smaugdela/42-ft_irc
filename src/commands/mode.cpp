/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:32:08 by fboumell          #+#    #+#             */
/*   Updated: 2022/11/04 18:06:58 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/*  Command: MODE
    Parameters: <nickname>
                *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )

    The user MODE's are typically changes which affect either how the
    client is seen by others or what 'extra' messages the client is sent.
    A user MODE command MUST only be accepted if both the sender of the
    message and the nickname given as a parameter are both the same.  If
    no other parameter is given, then the server will return the current
    settings for the nick.

    i - marks a users as invisible;
    w - user receives wallops;
    o - operator flag;

    Numeric Replies:
        ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
        ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS
*/

void mode(Server *serv, Message &msg)
{
    std::string str;

    if (msg.getParams().size() == 0)
    {
        str = ERR_NEEDMOREPARAMS;
        str += " " + msg.getSender()->getNickname() + " ";
        str += ":Error need more params.";
    }
    if (msg.getParams()[0] != msg.getSender()->getNickname())
    {
        str = ERR_USERSDONTMATCH;
        str += " " + msg.getSender()->getNickname() + " ";
        str += ":Cannot change mode for other users";
    }
    else
    {
        std::string mode = msg.getParams()[1];
        for (size_t i = 0; i < mode.size(); i++)
        {
            if (mode[i] == '+')
            {
                if(mode[i + 1] == 'i' || mode[i + 1] == 'w')
                {
                    serv->getUser(msg.getSender()->getNickname())->addMode(mode[i + 1]);
                    str = RPL_UMODEIS;
                    str += " " + msg.getSender()->getNickname() + " ";
                    str += "Your user mode is [+" + serv->getUser(msg.getSender()->getNickname())->getMode() + "]";
                    msg.getSender()->send_to(str.c_str());
                }
                else
                {
                    str = ERR_UMODEUNKNOWNFLAG;
                    str += " " + msg.getSender()->getNickname() + " ";
                    str += ":Unknown MODE flag";
                    msg.getSender()->send_to(str.c_str());
                }
            }
            if (mode[i] == '-')
            {
                if(mode[i + 1] == 'i' || mode[i + 1] == 'w')
                {
                    serv->getUser(msg.getSender()->getNickname())->rmMode(mode[i + 1]);
                    str = RPL_UMODEIS;
                    str += " " + msg.getSender()->getNickname() + " ";
                    str += "Your user mode is [+" + serv->getUser(msg.getSender()->getNickname())->getMode() + "]";
                    msg.getSender()->send_to(str.c_str());
                }
                else
                {
                    str = ERR_UMODEUNKNOWNFLAG;
                    str += " " + msg.getSender()->getNickname() + " ";
                    str += ":Unknown MODE flag";
                    msg.getSender()->send_to(str.c_str());
                }
            }
        }
    }
    msg.getSender()->send_to(str.c_str());
    // std::cout << "Mode is : " << serv->getUser(msg.getSender()->getNickname())->getMode() << std::endl;
}