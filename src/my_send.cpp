/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_send.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:54:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/10 14:35:04 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

void	my_send(Client const *client, std::string msg_str)
{
	if (client == NULL || client->getConnected() == false || client->getAuthorize() == false)
		return ;

	std::cout << "Message to client #" << client->getFd() << " (" << client->getNickname() << ") >> [" << msg_str << "]" << std::endl;

	msg_str += "\r\n";

	const char*	msg = msg_str.c_str();
	size_t	init_len = strlen(msg);
	size_t	actual_len = 0;
	ssize_t	ret = 0;

	while (actual_len < init_len)
	{
		ret = send(client->getFd(), &msg[actual_len], init_len - actual_len, MSG_NOSIGNAL);
		if (ret == -1)
		{
			std::cout << "Error send(): " << strerror(errno) << std::endl;
			return ;
		}
		actual_len += ret;
	}
}
