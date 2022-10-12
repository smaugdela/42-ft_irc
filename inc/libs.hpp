/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:11:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/12 16:04:22 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_HPP
# define LIBS_HPP

# include <cstdlib>
# include <string>
# include <iostream>
# include <fstream>
# include <map>
# include <memory.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <poll.h>

# define MAX_BACKLOGS	10
# define MAX_CLIENTS	42

typedef int	sockfd;

# include "proto.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Server.hpp"

#endif
