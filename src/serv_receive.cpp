/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_receive.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:48:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/22 01:33:39 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/* This function will parse the client's buffer into its commands list. */
static void	buf_to_cmd(Client *client)
{
	char	*buffer = strdup(client->getBuffer().c_str());
	std::list<std::string>	buf_list(split(buffer, "\r\n"));

	free(buffer);
	client->setBuffer("");

	for (std::list<std::string>::const_iterator it = buf_list.begin(); it != buf_list.end(); ++it)
	{
		std::cout << "Message from client #" << client->getFd() << ": [" << *it << "]" << std::endl;
		Message new_msg(client, NULL, *it);
		if (new_msg.parse_msg())
			client->commands.push_back(new_msg);
	}
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
		std::cout << "Message from client #" << client << " incomplete! Adding it to the buffer..." << std::endl;
		server->getUser(client)->setBuffer(server->getUser(client)->getBuffer() + buffer);
	}
	else
	{
		server->getUser(client)->setBuffer(server->getUser(client)->getBuffer() + buffer);
		buf_to_cmd(server->getUser(client));
	}
}
