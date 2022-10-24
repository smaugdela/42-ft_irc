/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/24 16:47:49 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class Configuration;

class Server
{

	public:

		Server(int ac, const char **av);
		~Server();

		bool	addUser(Client* new_user);
		void	rmUser(Client* user);
		Client*	getUser(sockfd	fd) const;
		Client*	getUser(std::string nickname) const;
		void	setCmdlist(void);

		int										getPort(void) const;
		std::string	const&						getPassword(void) const;
		sockfd									getListener(void) const;
		std::map<sockfd, Client*> const&		getUsers(void) const;
		std::map<std::string, Channel*> const&	getChans(void) const;
		std::map<std::string, void (*)(Server*, Message&)> const& getCmdList(void) const;
		Configuration* 							getConfig(void) const;

		void									setPort(int port);
		void									setPassword(std::string password);
		void									setListener(sockfd listener);

	private:

		Server();
		Server( Server const & src );
		Server &operator=( Server const & rhs );

		int								_port;
		std::string						_password;
		sockfd							_listener;
		std::map<std::string, void (*)(Server*, Message&)>		_cmdList;   // a init
		std::map<sockfd, Client*>		_users;
		std::map<std::string, Channel*>	_chans;
		Configuration					*_config;

};

std::ostream &			operator<<( std::ostream & o, Server const & i );

#endif /* ********************************************************** SERVER_H */
