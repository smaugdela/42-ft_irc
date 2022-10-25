/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_send.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:10:25 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/25 10:51:55 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/* Will send the messages that are ready to be sent. */
void	my_send(Client *client, const char *msg)
{
	std::string	packet;

	std::cout << "Message to client #" << client->getFd() << ": [" << msg << "]" << std::endl;
	send(client->getFd(), msg, strlen(msg), MSG_NOSIGNAL);
}
