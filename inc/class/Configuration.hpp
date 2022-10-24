/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:34:10 by fboumell          #+#    #+#             */
/*   Updated: 2022/10/24 15:52:25 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

class Configuration
{

	public:

		Configuration();
		~Configuration();

		std::string const&						getServerName(void) const;
		std::string const&						getServerVersion(void) const;
		std::string const&						getMotd(void) const;
		std::string const&						getInfoConfig(void) const;
		std::string const&						getOperUSer(void) const;
		std::string const&						getOperPass(void)	const;
		size_t									getPing(void) const;
		int										getTimeout(void) const;
		size_t									getMaxBacklogs(void) const;
		size_t									getMaxUsers(void) const;

		void									setServerName(std::string serverName);
		void									setServerVersion(std::string serverVersion);
		void									setMotd(std::string motd);
		void									setInfoConfig(std::string infoConfig);
		void									setOperUser(std::string operUser);
		void									setOperPass(std::string operPass);
		void									setPing(size_t ping);
		void									setTimeout(int timeOut);
		void									setMaxBacklogs(size_t maxBacklogs);
		void									setMaxUsers(size_t maxUsers);



	private:
	
		Configuration( Configuration const & src );
		Configuration &		operator=( Configuration const & rhs );

		std::string						_serverName;
		std::string						_serverVersion;
		std::string						_motd;
		std::string						_infoConfig;
		std::string						_operUser;
		std::string						_operPass;
		size_t							_ping;
		int								_timeout;
		size_t							_maxBacklogs;
		size_t							_maxUsers;
		

};

std::ostream &			operator<<( std::ostream & o, Configuration const & i );

#endif /* *************************************************** CONFIGURATION_H */