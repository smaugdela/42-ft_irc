/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:49 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/24 13:39:36 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

class Client;

class Message
{

	public:

		Message();
		Message( Message const & src );
		Message(Client *sender, Client *receiver, std::string message);
		~Message();

		Message	&operator=( Message const & rhs );

		bool	parse_msg(void);
		bool	Check_command(std::string str);

		std::string					getMessage(void) const;
		std::string const&			getCommand(void) const;
		std::string const&			getPrefix(void) const;
		std::vector<std::string>	const& getParams(void) const;
		Client*						getSender(void) const;
		Client*						getReceiver(void) const;
		void						setCommand(std::string command);
		void						setPrefix(std::string prefix);
		void						setParams(std::vector<std::string> params);

	private:

		Client*						_sender;
		Client*						_receiver;
		std::string					_message;
		std::string					_command;
		std::string 				_prefix;
		std::vector<std::string>	_params;

};

std::ostream &			operator<<( std::ostream & o, Message const & i );

#endif /* ********************************************************* MESSAGE_H */
