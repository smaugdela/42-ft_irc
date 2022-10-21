/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:53:22 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/21 17:24:13 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

std::vector<char*> split(char *str, const char *delim)
{
	char 	*ptr = strtok(str, delim);
	std::vector<char*> vect;

	while (ptr)
	{
		vect.push_back(strdup(ptr));
		ptr = strtok(NULL, delim);
	}
	return vect;
}
