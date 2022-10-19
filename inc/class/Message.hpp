/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:49 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/19 17:18:51 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

class Message
{

	public:

		Message();
		Message( Message const & src );
		Message(Client *sender, Client *receiver, char *message);
		~Message();

		char *getMessage(void) const;
		std::string const& getCommand(void) const;
		std::string const& getPrefix(void) const;
		std::string const& getParams(void) const;
		void	setCommand(std::string command);
		void	setPrefix(std::string prefix);
		void	setParams(std::string params);

		bool	Check_prefix(std::string str);
		bool	Check_command(std::string str);

	private:

		Message &		operator=( Message const & rhs );

		Client*		_sender;
		Client*		_receiver;
		char		*_message;
		std::string	_command;
		std::string _prefix;
		std::string _params;

};

std::ostream &			operator<<( std::ostream & o, Message const & i );

#endif /* ********************************************************* MESSAGE_H */
