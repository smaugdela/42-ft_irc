/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/26 14:41:24 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

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
					if (n == 0)		// The listening socket is at index 0.
						serv_accept(serv, fds);
					else if (n != 0)
						serv_receive(fds[n].fd, serv);
				}
				if (fds[n].revents & POLLHUP || fds[n].revents & POLLERR || fds[n].revents & POLLNVAL)
				{	
					std::cout << "Invalid event on socket #" << fds[n].fd << "." << std::endl;
					serv->getUser(fds[n].fd)->disconnect();
				}
			}
		}
		remove_deco_users(serv);
	}
}
