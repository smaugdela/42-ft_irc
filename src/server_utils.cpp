/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:27:33 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/27 16:11:30 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs.hpp"

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

	serv->setIpaddr(std::string(inet_ntoa(*reinterpret_cast<struct in_addr*>(&addr))));

	shield(listen(sock, serv->getConfig()->getMaxBacklogs()), -1, "listen", __FILE__, __LINE__);

	return sock;
}

void	error_ConfigFile(void)
{
	std::ifstream rules("src/config/rules.txt", std::ifstream::in);

	if (rules.good())
	{
		std::string str;
		while(getline(rules, str))
		{
			std::cout << str << std::endl;
		}
	}
	else
	{
		std::cout << "Error. File rules of configuration file not opened\n";
		exit(EXIT_FAILURE);
	}
	rules.close();
	exit(EXIT_FAILURE);
}

bool	setData(std::string str, Configuration *dataConfig)
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
	std::string tab[10] = {"name", "version", "motd", "info", "oper_user", "oper_password", "ping", "timeout", "max_backlogs", "max_users"};
	for (; i < 10 && *it != tab[i]; i++)
	{
		if (it == v.end())
			return false;
	}
	it++;
	std::string value = *it;
	
	switch (i)
	{
		case 0 :
				dataConfig->setServerName(value);
				break ;
			case 1 :
				dataConfig->setServerVersion(value);
				break ;
			case 2 :
				dataConfig->setMotd(value);
				break ;
			case 3 :
				dataConfig->setInfoConfig(value);
				break ;
			case 4 :
				dataConfig->setOperUser(value);
				break ;
			case 5 :
				dataConfig->setOperPass(value);
				break ;
			case 6 :
				dataConfig->setPing(strtoul(value.c_str(), NULL, 10));
				break ;
			case 7 :
				dataConfig->setTimeout(strtol(value.c_str(), NULL, 10));
				break ;
			case 8 :
				dataConfig->setMaxBacklogs(strtoul(value.c_str(), NULL, 10));
				break ;
			case 9 :
				dataConfig->setMaxUsers(strtoul(value.c_str(), NULL, 10));
				break ;
			default :
				return (false);
	}
	return (true);
}

void	setConfigData(Configuration *dataConfig)
{
	std::ifstream	ifs("src/config/file.config", std::ifstream::in);

	if (ifs.good())
	{
		std::string str;
		while (getline(ifs, str))
		{
			if (!str.empty())
			{
				std::string::iterator it = str.end();
				it--;
				if (*it == '=')
					error_ConfigFile();
				else 
					if (setData(str, dataConfig) == false)
						error_ConfigFile();
			}
			else
				getline(ifs, str);
		}
		if (dataConfig->getServerName().empty() || dataConfig->getServerVersion().empty() || dataConfig->getMotd().empty()
			|| dataConfig->getInfoConfig().empty() || dataConfig->getOperUSer().empty() || dataConfig->getOperPass().empty()
			|| dataConfig->getPing() < 10 || dataConfig->getTimeout() == 0 || dataConfig->getMaxBacklogs() == 0 || dataConfig->getMaxUsers() == 0)
				error_ConfigFile();
			
		std::cout << *dataConfig;
	}
	else
	{
		std::cout << "Error. File Configuration not opened\n";
		error_ConfigFile();
	}
	ifs.close();
}
