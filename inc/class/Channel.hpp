/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:06:16 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/12 14:42:48 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "libs.hpp"

class Channel
{

	public:

		Channel();
		Channel(std::string name);
		~Channel();

	private:

		Channel( Channel const & src );
		Channel &		operator=( Channel const & rhs );

		std::string					_name;
		std::map<sockfd, *Client>	_members;
		// Add attributes for the modes

};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */