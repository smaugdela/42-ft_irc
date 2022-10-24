/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:06:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/24 13:49:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: INFO
//    Parameters: [ <target> ]

//    The INFO command is REQUIRED to return information describing the
//    server: its version, when it was compiled, the patchlevel, when it
//    was started, and any other miscellaneous information which may be
//    considered to be relevant.

//    Wildcards are allowed in the <target> parameter.

void info(Server *serv, Message &msg)
{(void)serv; (void)msg;}