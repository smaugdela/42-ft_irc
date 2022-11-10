/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/10 14:34:06 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

static void	set_pollfd(Server *serv, std::vector<struct pollfd> &fds)
{
	fds.clear();

	if (serv == NULL)
		return ;

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
		if (it->second->getLastcom() >= serv->getConfig()->getPing())
			it->second->send_to("PING " + it->second->getNickname());
	}
}

static void	rm_deco_users(Server *serv)
{
	if (serv == NULL)
		return ;

	for (std::map<sockfd, Client*>::const_iterator it = serv->getUsers().begin(); it != serv->getUsers().end(); ++it)
	{
		if (it->second->getConnected() == false || it->second->getLastcom() >= serv->getConfig()->getPing() + (serv->getConfig()->getTimeout() / 1000))
		{
			std::cout << "Client at socket #" << it->first << " disconnected." << std::endl;

			Message quit_msg(it->second, "QUIT :Client disconnected.");
			quit_msg.parse_msg();
			quit(serv, quit_msg);

			it = serv->getUsers().begin();
			if (it == serv->getUsers().end())
				return ;
		}
	}
}

static void	rm_empty_chans(Server *serv)
{
	if (serv == NULL)
		return ;

	for (std::map<std::string, Channel *>::const_iterator it = serv->getChans().begin(); it != serv->getChans().end(); ++it)
	{
		if (it->second->getMembers().size() <= 0)
		{
			serv->rmChan(it->second);
			it = serv->getChans().begin();
			if (it == serv->getChans().end())
				return ;
		}
	}
}

void	server_loop(Server *serv)
{
	std::vector<struct pollfd> fds;

	while (serv != NULL && server_running)
	{
		set_pollfd(serv, fds);

		poll(fds.data(), fds.size(), serv->getConfig()->getTimeout());
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
		rm_deco_users(serv);
		rm_empty_chans(serv);
	}
}
