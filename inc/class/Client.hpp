/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/26 15:22:39 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

class Message;

class Client
{

	public:

		Client(int fd, struct sockaddr *addr);
		~Client();

		void						send_to(std::string msg_str) const;
		void						disconnect(void);
		void						welcome(Server *serv) const;

		sockfd						getFd(void) const;
		std::string const&			getNickname(void) const;
		std::string const&			getUsername(void) const;
		std::string const&			getRealname(void) const;
		bool						getAdm(void) const;
		bool						getAuthorize(void) const;
		bool						getConnected(void) const;
		std::string const&			getBuffer(void) const;

		void						setNickname(std::string new_nick);
		void						setUsername(std::string new_nick);
		void						setRealname(std::string new_nick);
		void						setAdm(bool	new_adm);
		void						setBuffer(std::string new_buffer);
		void						setAuthorize(bool authorization);

	private:

		sockfd const			_fd;
		std::string const		_hostname;
		bool					_connected;
		bool					_authorize;
		bool					_adm;	// Operator or not
		std::string				_nickname; // nickname - name which appears for other users
		std::string				_username; //username - name you use to login, allows system to identify you
		std::string				_realname; // real name - this is just additional information about you
		std::string				_buffer;

		Client();
		Client( Client const & src );
		Client &operator=( Client const & rhs );

};

std::ostream &			operator<<( std::ostream & o, Client const & i );

#endif /* ********************************************************** CLIENT_H */
