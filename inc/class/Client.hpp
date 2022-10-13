/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/13 18:19:56 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

class Client
{

	public:

		Client();
		Client(int fd, struct sockaddr_in addr);
		~Client();

		sockfd						getFd(void) const;
		struct sockaddr_in const&	getAddr(void) const;
		std::string const&			getNickname(void) const;
		std::string const&			getUsername(void) const;
		std::string const&			getRealname(void) const;
		bool						getAdm(void) const;
		void						setNickname(std::string new_nick);
		void						setUsername(std::string new_nick);
		void						setRealname(std::string new_nick);
		void						setAdm(bool	new_adm);

	private:

		sockfd				_fd;
		struct sockaddr_in	_addr;
		std::string			_nickname; // nickname - name which appears for other users
		std::string			_username; //username - name you use to login, allows system to identify you
		std::string			_realname; // real name - this is just additional information about you
		bool				_adm;	// Operator or not

		// Here should be all the other attributes that will be needed by the commands

		Client( Client const & src );
		Client &	operator=( Client const & rhs );

};

std::ostream &			operator<<( std::ostream & o, Client const & i );

#endif /* ********************************************************** CLIENT_H */
