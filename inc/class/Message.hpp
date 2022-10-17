/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:49 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/17 17:30:54 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

class Message
{

	public:

		Message();
		Message( Message const & src );
		Message(Client *sender, Client *receiver, std::string message);
		~Message();

		std::string const& getMessage(void) const;

	private:

		Message &		operator=( Message const & rhs );

		Client*		_sender;
		Client*		_receiver;
		std::string	_message;
		std::string	_command;

};

std::ostream &			operator<<( std::ostream & o, Message const & i );

#endif /* ********************************************************* MESSAGE_H */