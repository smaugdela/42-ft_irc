/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:07:50 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/19 11:13:24 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: KILL         !!!  RECOMMENDED TO BE ONLY ALLOWED TO OPERATORS !!! 
//    Parameters: <nickname> <comment>


// FR : Vire la personne du serveur 
//    The KILL command is used to cause a client-server connection to be
//    closed by the server which has the actual connection.  Servers
//    generate KILL messages on nickname collisions.  It MAY also be
//    available available to users who have the operator status.

//    Clients which have automatic reconnect algorithms effectively make
//    this command useless since the disconnection is only brief.  It does
//    however break the flow of data and can be used to stop large amounts
//    of 'flooding' from abusive users or accidents.  Abusive users usually
//    don't care as they will reconnect promptly and resume their abusive
//    behaviour.  To prevent this command from being abused, any user may
//    elect to receive KILL messages generated for others to keep an 'eye'
//    on would be trouble spots.

//    In an arena where nicknames are REQUIRED to be globally unique at all
//    times, KILL messages are sent whenever 'duplicates' are detected
//    (that is an attempt to register two users with the same nickname) in
//    the hope that both of them will disappear and only 1 reappear.

//    When a client is removed as the result of a KILL message, the server
//    SHOULD add the nickname to the list of unavailable nicknames in an
//    attempt to avoid clients to reuse this name immediately which is
//    usually the pattern of abusive behaviour often leading to useless
//    "KILL loops".  See the "IRC Server Protocol" document [IRC-SERVER]
//    for more information on this procedure.

//    The comment given MUST reflect the actual reason for the KILL.  For
//    server-generated KILLs it usually is made up of details concerning
//    the origins of the two conflicting nicknames.  For users it is left
//    up to them to provide an adequate reason to satisfy others who see
//    it.  To prevent/discourage fake KILLs from being generated to hide
//    the identify of the KILLer, the comment also shows a 'kill-path'
//    which is updated by each server it passes through, each prepending
//    its name to the path.