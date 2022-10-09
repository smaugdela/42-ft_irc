/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:11:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/10 01:15:32 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_HPP
# define STRUCTS_HPP

# include "libs.hpp"

typedef struct s_serv_env{
	std::string		password;
	int				port;
	struct pollfd	*fds;
	nfds_t			nfds;
}	serv_env;

#endif
