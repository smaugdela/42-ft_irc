/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:40:31 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/24 10:49:47 by smagdela         ###   ########.fr       */
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
	Server serv(ac, av);

	signal(SIGINT, sig_handler);

	server_loop(&serv);

	return EXIT_SUCCESS;
}
