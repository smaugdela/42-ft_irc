/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:57:35 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/24 12:05:03 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"


//   Command: ERROR
//    Parameters: <error message>

//    The ERROR command is for use by servers when reporting a serious or
//    fatal error to its peers.  It may also be sent from one server to
//    another but MUST NOT be accepted from any normal unknown clients.

//    Only an ERROR message SHOULD be used for reporting errors which occur
//    with a server-to-server link.  An ERROR message is sent to the server
//    at the other end (which reports it to appropriate local users and
//    logs) and to appropriate local users and logs.  It is not to be
//    passed onto any other servers by a server if it is received from a
//    server.

//    The ERROR message is also used before terminating a client
//    connection.

//    When a server sends a received ERROR message to its operators, the
//    message SHOULD be encapsulated inside a NOTICE message, indicating
//    that the client was not responsible for the error.

void error(Server *serv, Message &msg)
{}