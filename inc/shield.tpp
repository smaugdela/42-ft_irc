/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shield.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:50:48 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/09 14:58:33 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

template<typename T>
T	shield(T ft, T error, const char *description, const char *file, int line)
{
	if (ft == error)
	{
		std::cerr << "Error in file " << file << " at line " << line << "." << std::endl;
		std::cerr << description << std::endl;
		exit(EXIT_FAILURE);
	}
	return ft;
}
