/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:42:57 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/10 14:22:56 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//   Command: OPER
//    Parameters: <name> <password>

//    A normal user uses the OPER command to obtain operator privileges.
//    The combination of <name> and <password> are REQUIRED to gain
//    Operator privileges.  Upon success, the user will receive a MODE
//    message (see section 3.1.5) indicating the new user modes.

//    Numeric Replies:

//            ERR_NEEDMOREPARAMS              RPL_YOUREOPER
//            ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

void oper(Server *serv, Message &msg)
{
	if (serv == NULL)
		return ;

	std::string str;

	if (msg.getParams().size() < 2)
	{
		str = ERR_NEEDMOREPARAMS;
		str += " " + msg.getSender()->getNickname() + " :Error need more params.";
		msg.getSender()->send_to(str);
	}
	else if (msg.getParams()[0] != serv->getConfig()->getOperUSer() || msg.getParams()[1] != serv->getConfig()->getOperPass())
	{
		str = ERR_PASSWDMISMATCH;
		str += " " + msg.getSender()->getNickname() + " :Password incorrect";
		msg.getSender()->send_to(str);
	}
	else
	{
		msg.getSender()->addMode('o');
		str = RPL_YOUREOPER;
		str += " " + msg.getSender()->getNickname() + " :You are now an IRC operator";
		msg.getSender()->send_to(str);
	}
}
