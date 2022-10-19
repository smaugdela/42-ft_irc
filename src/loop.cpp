/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/19 16:51:42 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

void	serv_accept(Server *serv)
{
	sockfd			new_client_fd;
	struct sockaddr	cs;
	socklen_t		cs_len = sizeof(cs);

	new_client_fd = shield(accept(serv->getListener(), &cs, &cs_len), -1, "accept", __FILE__, __LINE__);
	shield(fcntl(new_client_fd, F_SETFL, O_NONBLOCK), -1, "fcntl", __FILE__, __LINE__);

	Client *new_client = new Client(new_client_fd, cs);
	serv->addUser(new_client);

	std::cout << "New Client on socket #" << new_client_fd << std::endl;
	serv_receive(new_client_fd, serv);
}

static void	set_pollfd(Server *serv, struct pollfd *fds, nfds_t nfds)
{
	fds[0].fd = serv->getListener();
	fds[0].events = POLLIN;
	fds[0].revents = 0;

	size_t	i = 1;
	for (std::map<sockfd, Client*>::const_iterator it = serv->getUsers().begin(); it != serv->getUsers().end() && i < serv->getUsers().size() && i < nfds; ++it, i++)
	{
		fds[i].fd = (*it).first;
		fds[i].events = POLLIN;
		fds[i].revents = 0;
	}
}

static void	remove_unauth_users(Server *serv)
{
	for (std::map<sockfd, Client*>::const_iterator it = serv->getUsers().begin(); it != serv->getUsers().end(); ++it)
	{
		if (it->second->getAuthorize() == false)
		{
			serv->rmUser(it->second);
			std::cout << "Client at socket #" << it->first << " disconnected." << std::endl;
			it = serv->getUsers().begin();
			if (it == serv->getUsers().end())
				return ;
		}
	}
}

void	server_loop(Server *serv)
{
	int				nevents = 0;
	nfds_t			nfds = 0;
	struct pollfd	*fds = NULL;

	while (true)
	{
		remove_unauth_users(serv);
		nfds = serv->getUsers().size() + 1;
		fds = new struct pollfd[nfds];
		set_pollfd(serv, fds, nfds);

		std::cout << "Waiting for an event in poll()..." << std::endl;
		nevents = shield(poll(fds, nfds, TIMEOUT), -1, "poll", __FILE__, __LINE__);
		std::cout << "Event(s) found!" << std::endl;
		for (int n = 0; n < nevents; ++n)
		{
			std::cout << "n = " << n << " < nevents = " << nevents << std::endl;
			if (fds[n].revents != 0)
			{
				std::cout << "Checking socket #" << fds[n].fd << "..." << std::endl;
				if (n == 0 && fds[0].revents & POLLIN)	// The listening socket is at index 0.
				{
					std::cout << "There is an incoming connection on the listening socket! (#" << serv->getListener() << ")" << std::endl;
					serv_accept(serv);
				}
				if (n != 0 && fds[n].revents & POLLIN)
				{
					std::cout << "There is a message on socket #" << fds[n].fd << "!" << std::endl;
					serv_receive(fds[n].fd, serv);
				}
				if (fds[n].revents & POLLHUP)
					std::cout << "POLLHUP on socket #" << fds[n].fd << std::endl;
				if (fds[n].revents & POLLERR)
					std::cout << "POLLERR on socket #" << fds[n].fd << std::endl;
				if (fds[n].revents & POLLNVAL)
					std::cout << "POLLNVAL on socket #" << fds[n].fd << std::endl;
			}
		}
		delete [] fds;
	}
}
