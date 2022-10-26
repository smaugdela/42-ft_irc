/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_def.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:21:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/26 15:32:36 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_DEF_HPP
# define RPL_DEF_HPP

# define RPL_WELCOME    "001"		// "Welcome to the Internet Relay Network <nick>!<user>@<host>"
# define RPL_YOURHOST   "002"		// "Your host is <servername>, running version <ver>"
# define RPL_CREATED    "003"		// "This server was created <date>"
# define RPL_MYINFO     "004"		// "<servername> <version> <available user modes> <available channel modes>"
# define RPL_INFO       "371"       // ":<string>"
# define RPL_ENDOFINFO  "374"       // ":End of INFO list"
#endif
