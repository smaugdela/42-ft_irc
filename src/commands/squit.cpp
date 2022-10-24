/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:44:19 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/24 12:08:18 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: SQUIT
//    Parameters: <server> <comment>

//    The SQUIT command is available only to operators.  It is used to
//    disconnect server links.  Also servers can generate SQUIT messages on
//    error conditions.  A SQUIT message may also target a remote server
//    connection.  In this case, the SQUIT message will simply be sent to
//    the remote server without affecting the servers in between the
//    operator and the remote server.

//    The <comment> SHOULD be supplied by all operators who execute a SQUIT
//    for a remote server.  The server ordered to disconnect its peer
//    generates a WALLOPS message with <comment> included, so that other
//    users may be aware of the reason of this action.

//    Numeric replies:

//            ERR_NOPRIVILEGES                ERR_NOSUCHSERVER
//            ERR_NEEDMOREPARAMS

void squit(Server *serv, Message &msg)
{}