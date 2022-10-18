/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:49 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/17 17:51:54 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

class Message
{

	public:

		Message();
		Message(Client *sender, Client *receiver, char *message);
		~Message();

		std::string const& getMessage(void) const;

	private:

		Message( Message const & src );
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