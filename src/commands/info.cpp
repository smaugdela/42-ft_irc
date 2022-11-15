/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:06:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/11/15 12:09:17 by smagdela         ###   ########.fr       */
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
		close(fd);
    }
    return (time);
}

std::vector<std::string> parse_file_info(Server *serv)
{
    std::string                 str;
    time_t                      time = serv->getCreateDate();
    std::string                 time_started = ctime(&time);
    std::string                 time_compilation = get_time_compilation();
    std::ifstream               ifs("./src/config/info.txt", std::ifstream::in);
	std::vector<std::string>	ret;

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
	        ret.push_back(line);
        }
    }
    else
    {
        std::cout << "Error. File Info not opened\n";
        error_ConfigFile();
    }
    ifs.close();
    return ret;
}

void info(Server *serv, Message &msg)
{
	if (serv == NULL)
		return ;

    std::string                 str;
	std::vector<std::string>	ret;
    
    if (msg.getParams().size() > 1)
    {
        str = ERR_NOSUCHSERVER;
        str += " " + msg.getSender()->getNickname() + " ";
        str += serv->getConfig()->getServerName();
        str += " :No such server";
    }
    else if (msg.getParams().size() && msg.getParams()[0].compare(serv->getConfig()->getServerName()) != 0)
    {
        str = ERR_NOSUCHSERVER;
        str += " " + msg.getSender()->getNickname() + " ";
        str += serv->getConfig()->getServerName();
        str += " :No such server";
    }
    else
    {
		ret = parse_file_info(serv);
		for(std::vector<std::string>::const_iterator it = ret.begin(); it != ret.end(); ++it)
		{
            str = RPL_INFO;
            str += " " + msg.getSender()->getNickname() + " :";
            str += *it;
            msg.getSender()->send_to(str.c_str());
		}
		str = RPL_ENDOFINFO;
        str += " " + msg.getSender()->getNickname() + " ";
        str += ":End of /INFO list";
    }
    msg.getSender()->send_to(str.c_str());
}
