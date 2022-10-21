/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_send.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:10:25 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/22 01:46:57 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/* Will send the messages that are ready to be sent. */
void	serv_send(sockfd clientfd, Server *server)
{
	Client *client = server->getUser(clientfd);
	std::string	packet;

	while (client->to_send.size() > 0)
	{
		packet = client->to_send.front().getMessage();
		std::cout << "Message to client #" << clientfd << ": [" << packet << "]" << std::endl;
		send(clientfd, packet.c_str(), packet.size(), MSG_NOSIGNAL);
		client->to_send.pop_front();
	}
}
