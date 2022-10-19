/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:57:35 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/19 10:58:08 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: DIE     !!!! Operator only !!!! 

//    Parameters: None

//    An operator can use the DIE command to shutdown the server.  This
//    message is optional since it may be viewed as a risk to allow
//    arbitrary people to connect to a server as an operator and execute
//    this command.

//    The DIE command MUST always be fully processed by the server to which
//    the sending client is connected and MUST NOT be passed onto other
//    connected servers.