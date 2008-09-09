##
## Makefile for SocketServer in /home/candan_c/rendu/ekzay/server
## 
## Made by caner candan
## Login   <candan_c@epitech.net>
## 
## Started on  Wed Jul  9 21:31:38 2008 caner candan
## Last update Tue Sep  2 14:09:22 2008 caner candan
##

NAME		=	server

SRCS		=	main.cpp		\
			Server.cpp		\
			Client.cpp		\
			Socket.cpp		\
			SocketServer.cpp	\
			SocketClient.cpp	\
			SQLiteWrapper.cpp	\
			State.cpp		\
			Apache.cpp		\
			IceCast.cpp

OBJS		=	$(SRCS:.cpp=.o)

CC		=	g++
RM		=	rm -f

DEBUG_42	=	-g -DDEBUG
CHKERR		=	-W -Wall -Werror

INCLUDES_SQL	=	`pkg-config sqlite3 --cflags`
LIBRARY_SQL	=	`pkg-config sqlite3 --libs`

INCLUDES	=	-I. $(INCLUDES_SQL)
LIBRARY		=	-L. $(LIBRARY_SQL)

CFLAGS		+=	$(INCLUDES) $(CHKERR) $(DEBUG_$(DEBUG))
LDFLAGS		+=	$(LIBRARY)

.SUFFIXES	:	.cpp.o

$(NAME)		:	$(OBJS)
			$(CC) -o $@ $(OBJS) $(LDFLAGS)

all		:	$(NAME)

clean		:
			$(RM) *~
			$(RM) *.o
			$(RM) *.core

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re

.cpp.o		:
			$(CC) $(CFLAGS) -c $< -o $@
