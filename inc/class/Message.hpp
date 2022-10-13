/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:49 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/13 18:20:27 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

class Message
{

	public:

		Message();
		~Message();

	private:

		Message( Message const & src );
		Message &		operator=( Message const & rhs );

		std::string	_message;
		Client*		_sender;
		Client*		_receiver;
		std::string	_command;

};

std::ostream &			operator<<( std::ostream & o, Message const & i );

#endif /* ********************************************************* MESSAGE_H */