/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:06:16 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/03 14:25:08 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel
{

	public:

		Channel(std::string name);
		~Channel();

		void	broadcast(Client *sender, std::string msg_str) const;
		void	addMember(Client *member);
		void	kickMember(Client *member);

		std::string const&					getName(void) const;
		Client*								getMember(std::string member) const;
		std::map<sockfd, Client*> const&	getMembers(void);
		std::string const&					getTopic(void) const;
		void								setTopic(std::string topic);

	private:

		Channel();
		Channel( Channel const & src );
		Channel &operator=( Channel const & rhs );

		std::string					_name;
		std::string					_topic;
		std::map<sockfd, Client*>	_members;
		// Add attributes for the modes

};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */
