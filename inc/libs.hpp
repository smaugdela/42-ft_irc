/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:11:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/17 17:14:27 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_HPP
# define LIBS_HPP

# include <cstdlib>
# include <string>
# include <iostream>
# include <fstream>
# include <map>
# include <list>
# include <memory.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <poll.h>

# define MAX_BACKLOGS	10	// Maximum of pending connection request on listening socket.
# define MAX_CLIENTS	42	// Maximum of connected clients.
# define TIMEOUT		-1	// -1 means no timeout. Value in milliseconds.

typedef int	sockfd;

# include "class/Client.hpp"
# include "class/Message.hpp"
# include "class/Channel.hpp"
# include "class/Server.hpp"
# include "proto.hpp"

#endif
