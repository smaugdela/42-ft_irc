/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:40:31 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/04 18:05:01 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

bool server_running = true;

static void sig_handler(int lol)
{
	(void)lol;
	server_running = false;
}

int	main(int ac, const char **av)
{
	signal(SIGINT, sig_handler);

	try {
		Server serv(ac, av);
		server_loop(&serv);
	}
	catch(std::exception &e) {
		std::cout << "Bad configuration file." << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
