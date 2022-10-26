/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:40:31 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/26 15:36:28 by fboumell         ###   ########.fr       */
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
