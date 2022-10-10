/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:11:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/10 18:50:43 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_HPP
# define STRUCTS_HPP

# include "libs.hpp"
# include "irc.hpp"

typedef enum e_sock_type {
	FREE,
	SERVER,
	CLIENT
}	sock_type;

typedef struct s_socks {
	sockfd				fd;
	sock_type			type;
	struct epoll_event	event;
}	socks;

typedef struct s_serv_env{
	std::string		password;
	int				port;
	size_t			max_backlogs;
	sockfd			epoll_fd;
	std::map<sockfd, socks*>	socks_map;
}	serv_env;

#endif
