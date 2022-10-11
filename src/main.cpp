/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:40:31 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/11 17:54:21 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

static bool	parse_input(int ac, const char **av, serv_env* env)
{
	if (ac != 3)
		return (false);
	std::string	port(av[1]);
	std::string	pwrd(av[2]);
	if (port.find_first_not_of("0123456789") == std::string::npos)
	{
		long portint = strtol(port.c_str(), NULL, 10);
		if (port.size() > 5 || portint < 1 || portint > 65536)
		{
			return false;
		}
		env->password = pwrd;
		env->port = portint;
		return true;
	}
	else
		return false;
}

static void	init_env(serv_env* env)
{
	size_t			max;
	std::ifstream	ifs;

	ifs.open("/proc/sys/net/ipv4/tcp_max_syn_backlog");
	if (ifs.fail())
		max = MAX_BACKLOGS;
	else
		ifs >> max;
	ifs.close();
	env->max_backlogs = max;
	std::cout << "Max Backlogs: " << env->max_backlogs << std::endl;
}

static sockfd	start_listening(serv_env *env)
{
	struct protoent *protoent = shield<struct protoent*>(getprotobyname("tcp"), NULL, "getprotobyname", __FILE__, __LINE__);
	std::cout << "Protoent, prototcol name : " << protoent->p_name << "\nProtocol number : " << protoent->p_proto << std::endl;

	sockfd			sock = shield<sockfd>(socket(AF_INET, SOCK_STREAM, protoent->p_proto), -1, "socket", __FILE__, __LINE__);

	struct sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(env->port);
	memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
	shield(bind(sock, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)), -1, "bind", __FILE__, __LINE__);

	shield(listen(sock, env->max_backlogs), -1, "listen", __FILE__, __LINE__);
	std::cout << "Listening Socket : " << sock << std::endl;

	return sock;
}

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
					std::cout << "Communication with client at socket : " << fds[n].fd << std::endl;
					// Here we should communicate with the client using recv/send depending on the revent.
			}
		}
	}
}

int	main(int ac, const char **av)
{
	serv_env	env;
	socks		tmp;

	shield(parse_input(ac, av, &env), false, "Usage: ./ircserv <port> <password>", __FILE__, __LINE__);
	std::cout << "Port : " << env.port << "\nPassword : " << env.password << std::endl;

	init_env(&env);

	tmp.fd = start_listening(&env);
	tmp.type = SERVER;

	env.listener = tmp.fd;

	env.socks_map.insert(std::make_pair(tmp.fd, tmp));

	std::cout << "Listening socket type : " << env.socks_map[tmp.fd].type << std::endl;
	std::cout << "Checking listening socket value again : " << env.socks_map[tmp.fd].fd << std::endl;

	server_loop(&env);

	return EXIT_SUCCESS;
}
