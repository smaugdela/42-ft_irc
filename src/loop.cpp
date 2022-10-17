/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/17 15:36:51 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

void	serv_accept(Server *serv)
{
	sockfd			new_client_fd;
	struct sockaddr	cs;
	socklen_t		cs_len = sizeof(cs);

	new_client_fd = shield(accept(serv->getListener(), &cs, &cs_len), -1, "accept", __FILE__, __LINE__);

	Client *new_client = new Client(new_client_fd, cs);
	serv->addUser(new_client);

	std::cout << "New Client on socket #" << new_client_fd << std::endl;
}

void	serv_receive(sockfd client)
{
	char		buffer[512];
	ssize_t		len;

	len = shield(recv(client, buffer, 512, 0), static_cast<ssize_t>(-1), "recv", __FILE__, __LINE__);

	if (len > 0)
	{
		// std::string	buffer_str(buffer);
		std::cout << "Message from client at socket #" << client << " : ";
		// if (buffer_str.find("\r\n") != std::string::npos)
		// 	std::cout << buffer_str << std::endl;
		// else
		// 	std::cout << "Message incomplete." << std::endl;
	}
}

static void	set_pollfd(Server *serv, struct pollfd *fds)
{
	fds[0].fd = serv->getListener();
	fds[0].events = POLLIN;
	fds[0].revents = 0;

	size_t	i = 1;
	for (std::map<sockfd, Client*>::const_iterator it = serv->getUsers().begin(); it != serv->getUsers().end() && i < serv->getUsers().size(); ++it, ++i)
	{
		fds[i].fd = (*it).first;
		fds[i].events = POLLIN | POLLOUT;
		fds[i].revents = 0;
	}
}

void	server_loop(Server *serv)
{
	while (true)
	{
		nfds_t	nfds = serv->getUsers().size() + 1;
		struct pollfd	fds[nfds];
		set_pollfd(serv, fds);

		int	nevents = shield(poll(fds, nfds, TIMEOUT), -1, "poll", __FILE__, __LINE__);
		for (int n = 0; n < nevents; ++n)
		{
			if (fds[n].revents != 0)
			{
				if (n == 0)				// The listening socket is at index 0.
					serv_accept(serv);
				else
					serv_receive(fds[n].fd);
			}
		}
	}
}
