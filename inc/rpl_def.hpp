/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_def.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:21:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/27 11:52:42 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_DEF_HPP
# define RPL_DEF_HPP

# define RPL_WELCOME    "001"		// "Welcome to the Internet Relay Network <nick>!<user>@<host>"
# define RPL_YOURHOST   "002"		// "Your host is <servername>, running version <ver>"
# define RPL_CREATED    "003"		// "This server was created <date>"
# define RPL_MYINFO     "004"		// "<servername> <version> <available user modes> <available channel modes>"
# define RPL_VERSION    "351"       // "<version>.<debuglevel> <server> :<comments>"
# define RPL_INFO       "371"       // ":<string>"
# define RPL_MOTD       "372"       // ":- <text>"
# define RPL_ENDOFINFO  "374"       // ":End of INFO list"
# define RPL_MOTDSTART  "375"       // ":- <server> Message of the day - "
# define RPL_ENDOFMOTD  "376"       // ":End of MOTD command"

#endif

// [<prefix>] RPL/ERR <nickname> [<params>]
