/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:53:22 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/10 14:38:36 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

std::list<std::string> split(char *str, const char *delim)
{
	std::list<std::string> list;

	if (str == NULL)
		return list;

	char 	*ptr = strtok(str, delim);

	while (ptr)
	{
		list.push_back(std::string(ptr));
		ptr = strtok(NULL, delim);
	}
	return list;
}
