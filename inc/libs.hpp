/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:11:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/19 12:33:16 by ajearuth         ###   ########.fr       */
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
# include <cstring>
# include <vector>
# include <sstream>
# include <fstream>
# include <algorithm>

//colors 
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[0;36m"
# define RED "\033[4;31m"
# define RESET "\033[0m"

# define MAX_BACKLOGS	10	// Maximum of pending connection request on listening socket.
# define MAX_CLIENTS	42	// Maximum of connected clients.
# define TIMEOUT		-1	// -1 means no timeout. Value in milliseconds.

typedef int	sockfd;

# include "class/Client.hpp"
# include "class/Message.hpp"
# include "class/Channel.hpp"
# include "class/Server.hpp"
# include "proto.hpp"
# include "err_def.hpp"

#endif
