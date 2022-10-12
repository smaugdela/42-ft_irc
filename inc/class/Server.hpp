/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/12 14:50:33 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "libs.hpp"

class Server
{

	public:

		Server();
		~Server();

	private:

		Server( Server const & src );
		Server &		operator=( Server const & rhs );

		int								_port;
		std::string						_password;
		size_t							_max_backlogs;
		sockfd							_listener;
		std::map<sockfd, *Client>		_users;
		std::map<std::string, *Channel>	_chans;

};

std::ostream &			operator<<( std::ostream & o, Server const & i );

#endif /* ********************************************************** SERVER_H */
