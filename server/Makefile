##
## Makefile for SocketServer in /home/candan_c/rendu/ekzay/server
## 
## Made by caner candan
## Login   <candan_c@epitech.net>
## 
## Started on  Wed Jul  9 21:31:38 2008 caner candan
## Last update Mon Jul 14 22:48:49 2008 caner candan
##

NAME		=	server

SRCS		=	main.cpp		\
			Server.cpp		\
			Client.cpp		\
			Socket.cpp		\
			SocketServer.cpp	\
			SocketClient.cpp	\
			Service.cpp		\
			ServiceWeb.cpp		\
			ServiceStream.cpp

OBJS		=	$(SRCS:.cpp=.o)

CC		=	g++
RM		=	rm -f

DEBUG_42	=	-g
CHKERR		=	-W -Wall -Werror

INCLUDES	=	-I.
LIBRARY		=	-L.

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
