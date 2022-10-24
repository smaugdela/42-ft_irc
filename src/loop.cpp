/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/24 15:32:02 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

static void	serv_accept(Server *serv, std::vector<pollfd> &fds)
{
	sockfd			new_client_fd;
	struct sockaddr	cs;
	socklen_t		cs_len = sizeof(cs);

	new_client_fd = shield(accept(serv->getListener(), &cs, &cs_len), -1, "accept", __FILE__, __LINE__);
	shield(fcntl(new_client_fd, F_SETFL, O_NONBLOCK), -1, "fcntl", __FILE__, __LINE__);

	Client *new_client = new Client(new_client_fd, cs);
	serv->addUser(new_client);

	fds.push_back(pollfd());
	fds.back().fd = new_client_fd;
	fds.back().events = POLLIN | POLLOUT;
	fds.back().revents = POLLIN | POLLOUT;

	std::cout << "New Client on socket #" << new_client_fd << "." << std::endl;
}

static void	set_pollfd(Server *serv, std::vector<struct pollfd> &fds)
{
	fds.clear();
	fds.push_back(pollfd());
	fds.back().fd = serv->getListener();
	fds.back().events = POLLIN;
	fds.back().revents = 0;

	for (std::map<sockfd, Client*>::const_iterator it = serv->getUsers().begin(); it != serv->getUsers().end(); ++it)
	{
		fds.push_back(pollfd());
		fds.back().fd = it->first;
		fds.back().events = POLLIN;
		fds.back().revents = 0;
	}
}

static void	remove_deco_users(Server *serv)
{
	for (std::map<sockfd, Client*>::const_iterator it = serv->getUsers().begin(); it != serv->getUsers().end(); ++it)
	{
		if (it->second->getConnected() == false)
		{
			std::cout << "Client at socket #" << it->first << " disconnected." << std::endl;
			serv->rmUser(it->second);
			it = serv->getUsers().begin();
			if (it == serv->getUsers().end())
				return ;
		}
	}
}

void	server_loop(Server *serv)
{
	std::vector<struct pollfd> fds;

	while (server_running)
	{
		set_pollfd(serv, fds);

		poll(fds.data(), fds.size(), TIMEOUT);
		for (size_t n = 0; n < fds.size(); n++)
		{
			if (fds[n].revents != 0)
			{
				if (fds[n].revents & POLLIN)
				{
					if (n == 0)					// The listening socket is at index 0.
						serv_accept(serv, fds);
					else
						serv_receive(fds[n].fd, serv);
				}
				if (fds[n].revents & POLLOUT && n !=0)
					serv_send(fds[n].fd, serv);
				if (fds[n].revents & POLLHUP)
				{	
					std::cout << "POLLHUP on socket #" << fds[n].fd << "." << std::endl;
					serv->getUser(fds[n].fd)->disconnect();
				}
				if (fds[n].revents & POLLERR)
				{	
					std::cout << "POLLERR on socket #" << fds[n].fd << "." << std::endl;
					serv->getUser(fds[n].fd)->disconnect();
				}
				if (fds[n].revents & POLLNVAL)
				{	
					std::cout << "POLLNVAL on socket #" << fds[n].fd << "." << std::endl;
					serv->getUser(fds[n].fd)->disconnect();
				}
			}
		}
		remove_deco_users(serv);
	}
}
