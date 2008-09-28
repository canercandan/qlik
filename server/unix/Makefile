# Server EKZAY Makefile

PATH_BIN	=	.
PATH_SRC	=	../src
PATH_INCLUDE	=	.
PATH_LIBRARY	=	.

NAME		=	$(PATH_BIN)/server

SRCS		=	$(PATH_SRC)/main.cpp		\
			$(PATH_SRC)/Apache.cpp		\
			$(PATH_SRC)/Client.cpp		\
			$(PATH_SRC)/IceCast.cpp		\
			$(PATH_SRC)/SQLiteWrapper.cpp	\
			$(PATH_SRC)/Server.cpp		\
			$(PATH_SRC)/Socket.cpp		\
			$(PATH_SRC)/SocketClient.cpp	\
			$(PATH_SRC)/SocketServer.cpp	\
			$(PATH_SRC)/State.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXX		=	g++
RM		=	rm -f

SQLITE_INCLUDE	=	`pkg-config sqlite3 --cflags`
SQLITE_LIBRARY	=	`pkg-config sqlite3 --libs`

INCLUDES	+=	-I$(PATH_INCLUDE) $(SQLITE_INCLUDE)
LIBRARIES	+=	-L$(PATH_LIBRARY) $(SQLITE_LIBRARY)

DEBUG_42	=	-g -DDEBUG
COMPAT		+=	-D__BSD_VISIBLE
WARNINGS	+=	-W -Wall -Werror

CFLAGS		+=	$(INCLUDES) $(DEBUG_$(DEBUG)) $(COMPAT) $(WARNINGS)
LDFLAGS		+=	$(LIBRARIES)

.SUFFIXES	:	.cpp.o

$(NAME)		:	$(OBJS)
			$(CXX) -o $@ $(OBJS) $(LDFLAGS)

all		:	$(NAME)

clean		:
			-$(RM) $(PATH_SRC)/*~
			-$(RM) $(PATH_SRC)/*.o
			-$(RM) *.core

fclean		:	clean
			-$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re

.cpp.o		:
			$(CXX) $(CFLAGS) -c $< -o $@
