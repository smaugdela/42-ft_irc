/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:11:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/10 15:57:56 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_HPP
# define STRUCTS_HPP

# include "libs.hpp"

typedef enum e_sock_type {
	FREE,
	LISTEN,
	CLIENT
}	sock_type;

typedef struct s_serv_env{
	std::string		password;
	int				port;
	size_t			max_backlogs;
	std::
}	serv_env;

#endif
