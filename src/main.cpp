/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:40:31 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/12 16:57:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

static void	serv_accept(serv_env *env)
{
	struct sockaddr	cs;
	socklen_t		cs_len = sizeof(cs);
	socks			new_client_sock;

	new_client_sock.fd = shield(accept(env->listener, &cs, &cs_len), -1, "accept", __FILE__, __LINE__);
	new_client_sock.type = CLIENT;

	env->socks_map.insert(std::make_pair(new_client_sock.fd, new_client_sock));

	std::cout << "New Client! On socket : " << new_client_sock.fd << std::endl;
}

static void	serv_receive(serv_env *env, sockfd client)
{
	char	buffer[512];
	ssize_t	len;

	(void)env;

	len = shield(recv(client, buffer, 512, 0), static_cast<ssize_t>(-1), "recv", __FILE__, __LINE__);

	if (len)
	{
		std::cout << "Client at socket #" << client << " : ";
		std::cout << buffer << std::endl;
	}
}

static void	server_loop(serv_env *env)
{
	while (true)
	{
		nfds_t			nfds = env->socks_map.size();
		struct pollfd	fds[nfds];
		size_t 			i = 0;

		for (std::map<sockfd, socks>::iterator it = env->socks_map.begin(); it != env->socks_map.end() && i < env->socks_map.size(); ++it, ++i)
		{
			fds[i].fd = (*it).first;
			if ((*it).second.type == SERVER)
				fds[i].events = POLLIN;
			else if ((*it).second.type == CLIENT)
				fds[i].events = POLLIN | POLLOUT;
			else
				fds[i].events = 0;
			fds[i].revents = 0;
		}

		int	nevents;
		nevents = shield(poll(fds, nfds, -1), -1, "poll", __FILE__, __LINE__);

		for (int n = 0; n < nevents; ++n)
		{
			if (fds[n].revents != 0)
			{
				if (env->socks_map[fds[n].fd].type == SERVER)
					serv_accept(env);
				else if (env->socks_map[fds[n].fd].type == CLIENT)
					serv_receive(env, fds[n].fd);
					// Here we should communicate with the client using recv/send depending on the revent.
			}
		}
	}
}

int	main(int ac, const char **av)
{
	Server serv(ac, av);

	server_loop(&env);

	return EXIT_SUCCESS;
}
