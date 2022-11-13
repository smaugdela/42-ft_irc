/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/13 19:41:08 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

class Message;

class Client
{

	public:

		Client(int fd, struct sockaddr_in addr, std::string servername);
		~Client();

		void						send_to(std::string msg_str) const;
		void						disconnect(void);
		void						welcome(Server *serv);
		void						resetTime(void);
		size_t						getLastcom(void) const;
		std::string					getPrefix(void) const;
		void						addMode(char mode);
		void						rmMode(char mode);

		sockfd						getFd(void) const;
		std::string const&			getNickname(void) const;
		std::string const&			getUsername(void) const;
		std::string const&			getRealname(void) const;
		bool						getAuthorize(void) const;
		bool						getConnected(void) const;
		bool						getWelcome(void) const;
		std::string const&			getBuffer(void) const;
		std::string const&			getMode(void) const;

		void						setNickname(std::string new_nick);
		void						setUsername(std::string new_nick);
		void						setRealname(std::string new_nick);
		void						setBuffer(std::string new_buffer);
		void						setAuthorize(bool authorization);

	private:

		sockfd const			_fd;
		std::string				_hostaddr;
		std::string				_hostname;
		bool					_connected;
		std::string				_servername;
		bool					_authorize;
		std::string				_nickname;	// nickname - name which appears for other users
		std::string				_username;	// username - name you use to login, allows system to identify you
		std::string				_realname;	// real name - this is just additional information about you
		bool					_welcome;
		std::string				_buffer;
		time_t					_last_com;
		std::string				_mode;

		Client();
		Client( Client const & src );
		Client &operator=( Client const & rhs );

};

std::ostream &			operator<<( std::ostream & o, Client const & i );

#endif /* ********************************************************** CLIENT_H */
