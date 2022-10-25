/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:06:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/25 19:15:56 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

//    Command: INFO
//    Parameters: [ <target> ]

//    The INFO command is REQUIRED to return information describing the
//    server: its version, when it was compiled, the patchlevel, when it
//    was started, and any other miscellaneous information which may be
//    considered to be relevant.

//    Wildcards are allowed in the <target> parameter.

std::string get_Time_Compilation()
{
    int         fd;
    struct stat file;
    std::string time;

    if ((fd = open("./ircserv", O_RDONLY)) > 0)
    {
        fstat(fd, &file);
        time = ctime(&file.st_mtime); // st_mtime = time of last modification
        if (time[time.size() - 1] == '\n')
			time.resize(time.size() - 1);
    }
    return (time);
}

void info(Server *serv, Message &msg)
{
    // (void)serv; (void)msg;

    //ajouter End of /INFO list a la fin
}