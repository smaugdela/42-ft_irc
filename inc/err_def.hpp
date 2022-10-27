/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_def.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:32:03 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/27 15:29:56 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_DEF_HPP
# define ERR_DEF_HPP

//	Commandes responses

# define RPL_LISTEND				"323"		// ":End of LIST"


// General errors 
 
# define ERR_UNKNOWNERROR			"400"
# define ERR_NEEDMOREPARAMS			"461"		// "<command> :Not enough parameters"
# define ERR_ALREADYREGISTRED		"462 :Unauthorized command (already registered)"

// Commands errors

# define ERR_NOSUCHNICK				"401"		// "<nickname> :No such nick/channel"		        || the nickname parameter supplied to a command is currently unused.
# define ERR_NOSUCHCHANNEL			"403"		// "<channel name> :No such channel"		        || the given channel name is invalid.
# define ERR_NOSUCHSERVER           "402"       // "<server name> :No such server"                  || Used to indicate the server name given currently does not exist.
# define ERR_CANNOTSENDTOCHAN		"404"		// "<channel name> :Cannot send to channel"	        || the user is ban from the channel he wants to write 
# define ERR_WASNOSUCHNICK			"406"		// "<nickname> :There was no such nickname"	        || (IDK IF WE WILL USE THIS) returned by WHOWAS to indicate there is no history information for that nickname.
# define ERR_NOSUCHSERVICE			"408"		// "<service name> :No such service"		        || (IDK IF WE WILL USE THIS) returned to a client which is attempting to send a SQUERY to a service which does not exist.
# define ERR_NOORIGIN				"409"		// ":No origin specified"					        || PING or PONG message missing the originator parameter.
# define ERR_UNKNOWNCOMMAND			"421"		// "<command> :Unknown command"				        || to a registered client to indicate that the command sent is unknown by the server.
# define ERR_NOMOTD                 "422"       // ":MOTD File is missing"
# define ERR_NORECIPIENT			"411" 		// :No recipient given (<command>)"
# define ERR_NOTEXTTOSEND			"412"		// ":No text to send"
# define ERR_BADMASK				"415"		// "<mask> :Bad Server/host mask"
# define ERR_NONICKNAMEGIVEN		"431"		// ":No nickname given"						        || when a nickname parameter expected for a command and isn't found.
# define ERR_ERRONEUSNICKNAME		"432"		// "<nick> :Erroneous nickname"
# define ERR_NICKNAMEINUSE			"433"		// ":Nickname is already in use"
# define ERR_USERNOTINCHANNEL		"441"		// "<nick> <channel> :They aren't on that channel"  || Returned by the server to indicate that the target user of the command is not on the given channel. 
# define ERR_NOTONCHANNEL           "442"       // "<channel> :You're not on that channel"          || Returned by the server whenever a client tries to perform a channel affecting command for which the client isn't a member.
# define ERR_NEEDMOREPARAMS 		"461"		// ":Error need more params."
# define ERR_PASSWDMISMATCH			"464"		// ":Password incorrect"						    || to indicate a failed attempt at registering a connection for which a password was required and was either not given or incorrect.
# define ERR_YOUREBANNEDCREEP		"465"		// ":You are banned from this server"		        ||  after an attempt to connect and register yourself with a server you are banned from.
# define ERR_CHANNELISFULL			"471"		// "<channel> :Cannot join channel (+l)"		    || channel is full
# define ERR_BANNEDFROMCHAN			"474"		// "<channel> :Cannot join channel (+b)"		    || if you juste got kicked
# define ERR_NOPRIVILEGES			"481"		// ":Permission Denied- You're not an IRC operator"
# define ERR_CHANOPRIVSNEEDED		"482"		// "<channel> :You're not channel operator"

#endif
