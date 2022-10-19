/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:27:33 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/19 16:56:10 by fboumell         ###   ########.fr       */
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

	sockfd	sock = shield<sockfd>(socket(PF_INET, SOCK_STREAM, protoent->p_proto), -1, "socket", __FILE__, __LINE__);
	int optval = 1;
	shield(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)), -1, "setsockopt", __FILE__, __LINE__);
	shield(fcntl(sock, F_SETFL, O_NONBLOCK), -1, "fcntl", __FILE__, __LINE__);

	struct sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(serv->getPort());
	memset(addr.sin_zero, 0, sizeof(addr.sin_zero));

	shield(bind(sock, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)), -1, "bind", __FILE__, __LINE__);

	shield(listen(sock, serv->getMaxbacklogs()), -1, "listen", __FILE__, __LINE__);

	return sock;
}

bool	setData(std::string str, Server *dataConfig)
{
	int							i = 0;
	const char 					delim = '=';
	std::string					token;
	std::vector<std::string>	v;

	std::stringstream			ss(str);
	while (getline(ss, token, delim))
		v.push_back(token);

	std::vector<std::string>::iterator	it;
	it = std::find(v.begin(), v.end(), v[0]);
	std::string tab[8] = {"name", "version", "motd", "info", "oper_user", "oper_password", "ping", "timeout"};
	for (; i < 8 && *it != tab[i]; i++);
	it++;

	switch (i)
	{
		case 0 :
				dataConfig->setServerName(*it);
				break ;
			case 1 :
				dataConfig->setServerVersion(*it);
				break ;
			case 2 :
				dataConfig->setMotd(*it);
				break ;
			case 3 :
				dataConfig->setInfoConfig(*it);
				break ;
			case 4 :
				dataConfig->setOperUser(*it);
				break ;
			case 5 :
				dataConfig->setOperPass(*it);
				break ;
			case 6 :
				dataConfig->setPing(*it);
				break ;
			case 7 :
				dataConfig->setTimeout(*it);
				break ;
			default :
				return (false);
	}
	return (true);
}

//traiter erreur dans le cas ou il n'ya pas de valeur apres le '=' dans le fichier config
void	setConfigData(Server *dataConfig)
{
	std::ifstream	ifs("./config/file.config", std::ifstream::in);

	if(ifs.good())
	{
		std::string str;
		while (getline(ifs, str))
			if (setData(str, dataConfig) == false)
				std::cout << "Error file configuration\n";
	}
	else
		std::cout << "Error. File Configuration not opened\n";
	ifs.close();
}