/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:06:16 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/26 17:36:29 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel
{

	public:

		Channel();
		Channel(std::string name);
		~Channel();

		void	broadcast(std::string msg_str) const;

		std::string const&	getName(void) const;
		Client*				getMember(std::string member) const;
		std::map<sockfd, Client*> const&	getMembers(void) const;

	private:

		Channel( Channel const & src );
		Channel &operator=( Channel const & rhs );

		std::string					_name;
		std::map<sockfd, Client*>	_members;
		// Add attributes for the modes

};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */