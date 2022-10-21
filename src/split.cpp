/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:53:22 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/22 01:19:42 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

std::list<std::string> split(char *str, const char *delim)
{
	char 	*ptr = strtok(str, delim);
	std::list<std::string> list;

	while (ptr)
	{
		list.push_back(std::string(ptr));
		ptr = strtok(NULL, delim);
	}
	return list;
}
