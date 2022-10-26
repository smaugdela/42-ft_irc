/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:41:25 by smagdela          #+#    #+#             */
/*   Updated: 2022/10/26 15:04:13 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_HPP
# define PROTO_HPP

/* Templates */

template<typename T>
T	shield(T ft, T error, const char *description, const char *file, int line);
# include "shield.tpp"

/* Functions */

bool	                parse_input(int ac, const char **av, Server *serv);
sockfd	                start_listening(Server *serv);
void	                server_loop(Server *serv);
void	                serv_receive(sockfd client, Server *server);
bool	                setData(std::string str, Configuration*dataConfig);
void	                setConfigData(Configuration *dataConfig);
void	                error_ConfigFile(void);
std::list<std::string>  split(char *str, const char *delim);
std::string             get_time_compilation();
std::string            parse_file_info(Server *serv);

/* Commandes */

void info(Server *serv, Message &msg);
void join(Server *serv, Message &msg);
void kick(Server *serv, Message &msg);
void my_kill(Server *serv, Message &msg);
void list(Server *serv, Message &msg);
void motd(Server *serv, Message &msg);
void names(Server *serv, Message &msg);
void nick(Server *serv, Message &msg);
void oper(Server *serv, Message &msg);
void part(Server *serv, Message &msg);
void pass(Server *serv, Message &msg);
void ping(Server *serv, Message &msg);
void pong(Server *serv, Message &msg);
void privmsg(Server *serv, Message &msg);
void quit(Server *serv, Message &msg);
void user(Server *serv, Message &msg);
void version(Server *serv, Message &msg);

#endif
