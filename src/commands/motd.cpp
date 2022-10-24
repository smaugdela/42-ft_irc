/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:24:21 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/24 12:06:34 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libs.hpp"

//       Command: MOTD
//    Parameters: [ <target> ]

//    The MOTD command is used to get the "Message Of The Day" of the given
//    server, or current server if <target> is omitted.

//    Wildcards are allowed in the <target> parameter.

//    Numeric Replies:
//            RPL_MOTDSTART                   RPL_MOTD

void motd(Server *serv, Message &msg)
{}