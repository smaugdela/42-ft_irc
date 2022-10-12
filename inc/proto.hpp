/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:41:25 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/12 13:48:25 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_HPP
# define PROTO_HPP

/* Templates Here */
template<typename T>
T	shield(T ft, T error, const char *description, const char *file, int line);
# include "shield.tpp"

#endif
