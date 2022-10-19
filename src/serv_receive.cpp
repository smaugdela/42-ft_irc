/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_receive.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:48:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/19 16:39:08 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

static std::list<Message*>	interpret_buffer(sockfd client, Server *server, char *buffer)
{
	std::list<Message*> msg_list;
	std::string			buffer_str;
	char				*ptr;

	buffer_str = server->getUser(client)->getBuffer() + buffer;

	if (buffer_str.find("\r\n", 0) == std::string::npos)
		server->getUser(client)->setBuffer(buffer_str);
	else
	{
		buffer = strdup(buffer_str.c_str());
		ptr = strtok(buffer, "\r\n");
		while(ptr)
		{
			msg_list.push_back(new Message(server->getUser(client), NULL, ptr));
			ptr = strtok(NULL, "\r\n");
		}
		server->getUser(client)->setBuffer("");
	}
	return msg_list;
}

void	serv_receive(sockfd client, Server *server)
{
	char					buffer[BUFFER_SIZE + 1];
	ssize_t					len;

	memset(buffer, 0, BUFFER_SIZE + 1);
	len = recv(client, buffer, BUFFER_SIZE, 0);

	std::cout << "Buffer len = " << len << std::endl;
	if (errno != EAGAIN && len == -1)
		shield(true, true, "recv", __FILE__, __LINE__);
	else if (len > 0)
	{
		std::list<Message*> msg_list = interpret_buffer(client, server, buffer);
		for (std::list<Message*>::iterator	it = msg_list.begin(); it != msg_list.end(); ++it)
			std::cout << "Message: [" << (*it)->getMessage() << "]" << std::endl;
	}
	else if (len == 0)
	{
		server->rmUser(server->getUser(client));
		std::cout << "Client at socket #" << client << " disconnected." << std::endl;
	}

	std::cout << "--------------------------------------------" << std::endl;
}