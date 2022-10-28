/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_accept.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:41:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/28 19:29:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

void	serv_accept(Server *serv, std::vector<pollfd> &fds)
{
	sockfd			new_client_fd;
	struct sockaddr	cs;
	socklen_t		cs_len = sizeof(cs);

	new_client_fd = shield(accept(serv->getListener(), &cs, &cs_len), -1, "accept", __FILE__, __LINE__);
	shield(fcntl(new_client_fd, F_SETFL, O_NONBLOCK), -1, "fcntl", __FILE__, __LINE__);

	Client *new_client = new Client(new_client_fd, *reinterpret_cast<struct sockaddr_in*>(&cs), serv->getConfig()->getServerName());
	serv->addUser(new_client);

	if (serv->getUsers().size() > serv->getConfig()->getMaxUsers())
	{
		new_client->disconnect();
		fds.push_back(pollfd());
		fds.back().fd = new_client_fd;
		fds.back().events = 0;
		fds.back().revents = 0;
		return ;
	}

	fds.push_back(pollfd());
	fds.back().fd = new_client_fd;
	fds.back().events = POLLIN;
	fds.back().revents = POLLIN;

	std::cout << "New Client on socket #" << new_client_fd << "." << std::endl;
}
