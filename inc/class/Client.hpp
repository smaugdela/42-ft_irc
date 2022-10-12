/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/12 14:32:07 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "libs.hpp"

class Client
{
	
	private:

		sockfd				_fd;
		struct sockaddr_in	_addr;
		std::string			_nickname;
		bool				_adm;	// Operator or not
		// Here should be all the other attributes that will be needed by the commands

		Client( Client const & src );
		Client &		operator=( Client const & rhs );

	public:

		Client();
		~Client();

		sockfd						getFd(void) const;
		struct sockaddr_in const&	getAddr(void) const;
		std::string const&			getNickname(void) const;
		bool						getAdm(void) const;
		void						setNickname(std::string new_nick);
		void						setAdm(bool	new_adm);

};

std::ostream &			operator<<( std::ostream & o, Client const & i );

#endif /* ********************************************************** CLIENT_H */
