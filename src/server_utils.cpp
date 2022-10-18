/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:27:33 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/18 15:31:30 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs.hpp"

static size_t	init_backlog(void)
{
	std::ifstream	ifs;
	size_t			tmp;

	ifs.open("/proc/sys/net/ipv4/tcp_max_syn_backlog");
	if (ifs.fail())
		tmp = MAX_BACKLOGS;
	else
		ifs >> tmp;
	ifs.close();
	return (tmp);
}

bool	parse_input(int ac, const char **av, Server* serv)
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
		serv->setPassword(pwrd);
		serv->setPort(portint);
		serv->setMaxbacklogs(init_backlog());
		return true;
	}
	else
		return false;
}

sockfd	start_listening(Server *serv)
{
	struct protoent *protoent = shield<struct protoent*>(getprotobyname("tcp"), NULL, "getprotobyname", __FILE__, __LINE__);

	sockfd	sock = shield<sockfd>(socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, protoent->p_proto), -1, "socket", __FILE__, __LINE__);

	struct sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(serv->getPort());
	memset(addr.sin_zero, 0, sizeof(addr.sin_zero));

	shield(bind(sock, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)), -1, "bind", __FILE__, __LINE__);

	shield(listen(sock, serv->getMaxbacklogs()), -1, "listen", __FILE__, __LINE__);

	return sock;
}
