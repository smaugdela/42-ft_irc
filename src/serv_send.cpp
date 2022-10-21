/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_send.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:10:25 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/20 17:25:32 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/* Will send the messages that are ready to be sent. */
void	serv_send(sockfd clientfd, Server *server)
{
	Client *client = server->getUser(clientfd);

	(void)server;
	(void)client;

}
