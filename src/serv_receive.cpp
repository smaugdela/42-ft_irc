/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_receive.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:48:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/21 17:53:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/* This function will parse the client's buffer into its commands list. */
static void	buf_to_cmd(Client *client)
{
	std::vector<char*>	vect;
	std::list<Message>	msg_list;
	char	*buffer = strdup(client->getBuffer().c_str());

	vect = split(buffer, "\r\n");
	delete buffer;
	client->setBuffer("");

	for (std::vector<char*>::const_iterator it = vect.begin(); it != vect.end(); ++it)
	{
		Message new_msg(client, NULL, *it);
		if (new_msg.parse_msg())
			msg_list.push_back(new_msg);
	}

	for (std::list<Message>::const_iterator it = msg_list.begin(); it != msg_list.end(); ++it)
		std::cout << "Message:\n" << *it << std::endl;
}

void	serv_receive(sockfd client, Server *server)
{
	char					buffer[BUFFER_SIZE + 1];
	ssize_t					len;

	memset(buffer, 0, BUFFER_SIZE + 1);
	len = recv(client, buffer, BUFFER_SIZE, MSG_DONTWAIT);
	std::string	buf_str(buffer);

	if (len < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
	{
		std::cout << "Error recv(): " << strerror(errno) << std::endl;
		server->getUser(client)->setConnected(false);
	}
	else if (len == 0)
		server->getUser(client)->setConnected(false);
	else if (len > 0 && (buf_str.rfind("\r\n") != buf_str.size() - 2))
	{
		std::cout << "Message from client #" << client << ":" << std::endl;
		std::cout << "Message incomplete! Adding it to the buffer..." << std::endl;
		server->getUser(client)->setBuffer(server->getUser(client)->getBuffer() + buffer);
	}
	else
	{
		std::cout << "Message from client #" << client << ":" << std::endl;
		server->getUser(client)->setBuffer(server->getUser(client)->getBuffer() + buffer);
		buf_to_cmd(server->getUser(client));
	}
}
