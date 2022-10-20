/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_receive.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:48:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/20 17:36:57 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

// static std::list<Message*>	interpret_buffer(sockfd client, Server *server, char *buffer)
// {
// 	std::list<Message*> msg_list;
// 	std::string			buffer_str;
// 	char				*ptr;

// 	buffer_str = server->getUser(client)->getBuffer() + buffer;

// 	if (buffer_str.find("\r\n", 0) == std::string::npos)
// 		server->getUser(client)->setBuffer(buffer_str);
// 	else
// 	{
// 		buffer = strdup(buffer_str.c_str());
// 		ptr = strtok(buffer, "\r\n");
// 		while(ptr)
// 		{
// 			msg_list.push_back(new Message(server->getUser(client), NULL, ptr));
// 			ptr = strtok(NULL, "\r\n");
// 		}
// 		server->getUser(client)->setBuffer("");
// 	}
// 	return msg_list;
// }

/* This function will parse the client's buffer into its commands list. */
static void	buf_to_cmd(Client *client)
{
	// std::list<Message*> msg_list;
	char	*buffer = strdup(client->getBuffer().c_str());
	char	*ptr = NULL;

	ptr = strtok(buffer, "\r\n");
	while(ptr)
	{
		std::cout << "Message: [" << ptr << "]" << std::endl;
		// msg_list.push_back(new Message(client, NULL, strdup(ptr)));
		ptr = strtok(NULL, "\r\n");
	}

	delete buffer;
	client->setBuffer("");

	// std::cout << "Here1" << std::endl;
	// for (std::list<Message*>::iterator it = msg_list.begin(); it != msg_list.end(); ++it)
	// {
	//	std::cout << "Here2" << std::endl;
	// 	std::cout << "Message: [" << (*it)->getMessage() << "]" << std::endl;
	// }
	// std::cout << "Here3" << std::endl;
}

void	serv_receive(sockfd client, Server *server)
{
	char					buffer[BUFFER_SIZE + 1];
	ssize_t					len;

	memset(buffer, 0, BUFFER_SIZE + 1);
	len = recv(client, buffer, BUFFER_SIZE, MSG_DONTWAIT);

	if (len < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
	{
		std::cout << "Error recv(): " << strerror(errno) << std::endl;
		server->getUser(client)->setConnected(false);
	}
	else if (len == 0)
		server->getUser(client)->setConnected(false);
	else if (len > 0 && !strncmp(buffer + len - 3, "\r\n", 2))
	{
		std::cout << "Message from client #" << client << ":" << std::endl;
		std::cout << "Message incomplete! Adding it to the buffer..." << std::endl;
		server->getUser(client)->setBuffer(server->getUser(client)->getBuffer() + buffer);
	}
	else
	{
		std::cout << "Message from client #" << client << ":" << std::endl;
		server->getUser(client)->setBuffer(server->getUser(client)->getBuffer() + buffer);
		// std::cout << "Buffer = [" << server->getUser(client)->getBuffer() << "]" << std::endl;
		buf_to_cmd(server->getUser(client));
	}
}
