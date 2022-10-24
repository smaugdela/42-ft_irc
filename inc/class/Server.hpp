/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/24 13:31:07 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class Server
{

	public:

		Server(int ac, const char **av);
		~Server();

		bool	addUser(Client* new_user);
		void	rmUser(Client* user);
		Client*	getUser(sockfd	fd) const;
		Client*	getUser(std::string nickname) const;

		int										getPort(void) const;
		std::string	const&						getPassword(void) const;
		size_t									getMaxbacklogs(void) const;
		sockfd									getListener(void) const;
		std::map<sockfd, Client*> const&		getUsers(void) const;
		std::map<std::string, Channel*> const&	getChans(void) const;
		std::map<std::string, void (*)(Server*, Message&)> const& getCmdList(void) const;
		std::string const&						getServerName(void) const;
		std::string const&						getServerVersion(void) const;
		std::string const&						getMotd(void) const;
		std::string const&						getInfoConfig(void) const;
		std::string const&						getOperUSer(void) const;
		std::string const&						getOperPass(void)	const;
		std::string const&						getPing(void) const;
		std::string const&						getTimeout(void) const;

		void									setPort(int port);
		void									setPassword(std::string password);
		void									setMaxbacklogs(size_t log);
		void									setListener(sockfd listener);
		void									setServerName(std::string serverName);
		void									setServerVersion(std::string serverVersion);
		void									setMotd(std::string motd);
		void									setInfoConfig(std::string infoConfig);
		void									setOperUser(std::string operUser);
		void									setOperPass(std::string operPass);
		void									setPing(std::string ping);
		void									setTimeout(std::string timeOut);
		void									setCmdlist(void);

	private:

		Server();
		Server( Server const & src );
		Server &		operator=( Server const & rhs );


		int								_port;
		std::string						_password;
		size_t							_max_backlogs;
		sockfd							_listener;
		std::map<std::string, void (*)(Server*, Message&)>		_cmdList;   // a init
		std::map<sockfd, Client*>		_users;
		std::map<std::string, Channel*>	_chans;
		std::string						_serverName;
		std::string						_serverVersion;
		std::string						_motd;
		std::string						_infoConfig;
		std::string						_operUser;
		std::string						_operPass;
		std::string						_ping;
		std::string						_timeout;

};

std::ostream &			operator<<( std::ostream & o, Server const & i );

#endif /* ********************************************************** SERVER_H */
