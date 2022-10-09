/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:40:31 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/09 15:10:50 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

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

static sockfd	start_listening(serv_env *env)
{
	// Should return a listening socket that will be added to poll_fd, or an invalid sockfd to indicate an error.
}

int	main(int ac, const char **av)
{
	serv_env	env;

	shield(parse_input(ac, av, &env), false, "Usage: ./ircserv <port> <password>", __FILE__, __LINE__);
	std::cout << "Port : " << env.port << "\nPassword : " << env.password << std::endl;
	
	// Use start_listening function to open a socket, bind it, and listen onto it.

	return EXIT_SUCCESS;
}
