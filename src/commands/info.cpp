/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:06:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/10/26 15:36:35 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/* Command: INFO
   Parameters: [ <target> ]

   The INFO command is REQUIRED to return information describing the
   server: its version, when it was compiled, the patchlevel, when it
   was started, and any other miscellaneous information which may be
   considered to be relevant.
   Wildcards are allowed in the <target> parameter.*/

std::string get_time_compilation()
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

std::string parse_file_info(Server *serv)
{
    std::string     str;
    time_t          time = serv->getCreateDate();
    std::string     time_started = ctime(&time);
    std::string     time_compilation = get_time_compilation();
    std::ifstream   ifs("./src/config/info.txt", std::ifstream::in);
    
    if (ifs.good())
    {
        size_t          pos;
        std::string     line;
        
        while (getline(ifs, line))
        {
            if ((pos = line.find("$SERVER_NAME")) != std::string::npos)
            {
                str = line.substr(0, pos) + serv->getConfig()->getServerName() + line.substr(pos + strlen("$SERVER_NAME"));
                line = str;
            }
            if ((pos = line.find("$SERVER_VERSION")) != std::string::npos)
            {
                str = line.substr(0, pos) + serv->getConfig()->getServerVersion() + line.substr(pos + strlen("$SERVER_VERSION"));
                line = str;
            }
            if (((pos = line.find("$COMPILATION_TIME")) != std::string::npos))
            {
                str = line.substr(0, pos) + time_compilation + line.substr(pos + strlen("$COMPILATION_TIME"));
                line = str;
            }
            if (((pos = line.find("$STARTED_TIME")) != std::string::npos))
            {
                str = line.substr(0, pos) + time_started + line.substr(pos + strlen("$STARTED_TIME"));
                line = str;
            }
        }
        return (line);
    }
    else
    {
        std::cout << "Error. File Info not opened\n";
        error_ConfigFile();
    }
    ifs.close();
    return "";    
}

void info(Server *serv, Message &msg)
{
    std::string str;
    
    if (msg.getParams().size() > 1)
    {
        str = ERR_NOSUCHSERVER;
        str += " ";
        str += serv->getConfig()->getServerName();
        str += " :No such server";
    }
    std::string target = msg.getParams()[0];
    if (target.compare(serv->getConfig()->getServerName()) != 0)
    {
        str = ERR_NOSUCHSERVER;
        str += " ";
        str += serv->getConfig()->getServerName();
        str += " :No such server";
    }
    else
    {
        while(parse_file_info(serv) != "")
        {
            str = RPL_INFO;
            str += " ";
            str += parse_file_info(serv);
            msg.getSender()->send_to(str.c_str());
        }
        str = RPL_ENDOFINFO;
        str += " ";
        str += ":End of INFO list";
        msg.getSender()->send_to(str.c_str());
    }
}