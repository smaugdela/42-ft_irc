/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:20:53 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/24 13:49:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

// ON LA MET OU PAS ?
// <channel>: Channel to modify/view.
// <topic>: If given, the new topic to set on the channel.
// A TOPIC message sent from the server indicates that the topic has been changed.
//  In this case, the <prefix> is the user that’s changed the topic. If a chanop’s TOPIC
//  command is successful, they receive one of these messages. In addition, all other clients 
//  in the channel also receive a TOPIC message. For example, if dan and alice are on #v4, and 
//  dan sets a new topic (or unsets the topic), both of them will receive a TOPIC message
//  indicating that the topic’s been changed. The examples illustrate this in action.

void topic(Server *serv, Message &msg)
{(void)serv; (void)msg;}