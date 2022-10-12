/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shield.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:50:48 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/12 13:49:18 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto.hpp"

template<typename T>
T	shield(T ft, T error, const char *description, const char *file, int line)
{
	if (errno)
		std::cerr << strerror(errno) << std::endl;
	if (ft == error)
	{
		std::cerr << "Error in file " << file << " at line " << line << ": " << description << std::endl;
		exit(EXIT_FAILURE);
	}
	return ft;
}
