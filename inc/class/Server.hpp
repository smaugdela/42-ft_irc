/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/07 17:49:09 by ajearuth         ###   ########.fr       */
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

		bool		addUser(Client* new_user);
		void		rmUser(Client* user);
		Client*		getUser(sockfd	fd) const;
		Client*		getUser(std::string nickname) const;
		void		addChan(Channel* new_chan);
		Channel*	getChannel(std::string name) const;
		void		rmChan(Channel *chan);
		void		setCmdlist(void);
		void		broadcast(std::string msg_str) const;

		int										getPort(void) const;
		std::string	const&						getPassword(void) const;
		sockfd									getListener(void) const;
		std::map<sockfd, Client*> const&		getUsers(void) const;
		std::map<std::string, Channel*> const&	getChans(void) const;
		std::map<std::string, ft_cmd> const& 	getCmdList(void) const;
		Configuration* 							getConfig(void) const;
		time_t const&							getCreateDate(void) const;
		std::string const&						getIpaddr(void) const;

		void									setPort(int port);
		void									setPassword(std::string password);
		void									setListener(sockfd listener);
		void									setIpaddr(std::string ipaddr);

	private:

		Server();
		Server( Server const & src );
		Server &operator=( Server const & rhs );

		void _callbot(Channel *channel, Client *user, char *message);

		int								_port;
		std::string						_password;
		std::string						_ipaddr;
		Configuration					*_config;
		time_t							_create_date;
		sockfd							_listener;
		std::map<std::string, ft_cmd>	_cmdList;
		std::map<sockfd, Client*>		_users;
		std::map<std::string, Channel*>	_chans;

};

std::ostream &			operator<<( std::ostream & o, Server const & i );

#endif /* ********************************************************** SERVER_H */
