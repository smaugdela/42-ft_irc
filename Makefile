# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 14:22:11 by smagdela          #+#    #+#              #
#    Updated: 2022/10/24 14:04:43 by smagdela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${BIN}

#################
#       Variables       #
#################

BIN     =       ircserv

INCS    = 	libs.hpp \
			proto.hpp \
			err_def.hpp \
			shield.tpp \
			class/Client.hpp \
			class/Channel.hpp \
			class/Server.hpp \
			class/Message.hpp \
			class/Configuration.hpp \

SRCS    =	main.cpp \
			loop.cpp \
			serv_receive.cpp \
			serv_send.cpp \
			server_utils.cpp \
			split.cpp \
			class/Client.cpp \
			class/Channel.cpp \
			class/Server.cpp \
			class/Message.cpp \
			commands/error.cpp \
			commands/info.cpp \
			commands/join.cpp \
			commands/kick.cpp \
			commands/kill.cpp \
			commands/list.cpp \
			commands/motd.cpp \
			commands/names.cpp \
			commands/nick.cpp \
			commands/oper.cpp \
			commands/part.cpp \
			commands/ping.cpp \
			commands/pong.cpp \
			commands/privmsg.cpp \
			commands/quit.cpp \
			commands/squit.cpp \
			commands/stats.cpp \
			commands/topic.cpp \
			commands/user.cpp \

OBJS    =       ${SRCS:.cpp=.o}

INCD    =       inc/
SRCD    =       src/
OBJD    =       obj/

INCS    :=      ${addprefix ${INCD},${INCS}}
OBJS    :=      ${addprefix ${OBJD},${OBJS}}
SRCS    :=      ${addprefix ${SRCD},${SRCS}}

CXX             =       g++
CXXFLAGS        =       -g -std=c++98 -Wall -Wextra -Werror

#################
#       Fancy Stuff     #
#################

GREY    =       \033[0;30m
RED     =       \033[0;31m
GREEN   =       \033[0;32m
YELLOW  =       \033[0;33m
BLUE    =       \033[0;34m
PURPLE  =       \033[0;35m
WHITE   =       \033[0;37m
CYAN    =       \033[0;96m

S_GREY  =       \033[1;30m
S_RED   =       \033[1;31m
S_GREEN =       \033[1;32m
S_YELLOW         =      \033[1;33m
S_BLUE  =       \033[1;34m
S_PURPLE         =      \033[1;35m
S_WHITE =       \033[1;37m
S_CYAN  =       \033[1;96m

BOLD    =       \033[1m
NC      =       \033[0m

# Box Drawing Unicode
# ┌─┬─┐
# │ │ │
# ├─┼─┤
# │ │ │
# └─┴─┘

#############
#       Rules   #
#############

all:    ${BIN}

${OBJD}%.o:     ${SRCD}%.cpp
		@echo "${S_CYAN}➤ Compiling $@...${NC}"
		@mkdir -p ${OBJD}
		@mkdir -p ${OBJD}/class
		@mkdir -p ${OBJD}/commands
		@${CXX} ${CXXFLAGS} -c -o $@ -I${INCD} $<
		@echo "${S_GREEN}✔ Object file built!\n${NC}"

${BIN}: ${OBJS}
		@echo "${S_CYAN}➤ Compiling $@...${NC}"
		@${CXX} ${CXXFLAGS} ${OBJS} -o ${BIN}
		@echo "${S_GREEN}✔ Binary available!\n${NC}"

clean:
		@echo "${S_RED}➤ Deleting object files...${NC}"
		@-rm -rf ${OBJD}
		@echo "${S_GREEN}✔ Object files deleted!\n${NC}"

fclean: clean
		@echo "${S_RED}➤ Deleting executable...${NC}"
		@-rm -rf ${BIN}
		@echo "${S_GREEN}✔ Executable deleted!\n${NC}"

re:     fclean  all

.PHONY: all clean fclean re
