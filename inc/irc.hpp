/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:41:25 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/11 17:04:45 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# define MAX_BACKLOGS	10
# define MAX_CLIENTS	42

typedef int	sockfd;

/* Templates Here */
template<typename T>
T	shield(T ft, T error, const char *description, const char *file, int line);
# include "shield.tpp"

#endif
