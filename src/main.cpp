/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:40:31 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/20 11:32:51 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

int	main(int ac, const char **av)
{
	Server serv(ac, av);

	server_loop(&serv);

	return EXIT_SUCCESS;
}
