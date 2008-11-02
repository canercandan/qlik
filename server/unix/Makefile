# Server EKZAY Makefile

PATH_BIN	=	.
PATH_SRC	=	../src
PATH_INCLUDE	=	.
PATH_LIBRARY	=	.
PATH_COMMON	=	../../common/src

NAME		=	$(PATH_BIN)/server

SRCS		=	$(PATH_SRC)/main.cpp		\
			$(PATH_SRC)/Action.cpp		\
			$(PATH_SRC)/Apache.cpp		\
			$(PATH_SRC)/Client.cpp		\
			$(PATH_SRC)/Config.cpp		\
			$(PATH_SRC)/Credit.cpp		\
			$(PATH_SRC)/Database.cpp	\
			$(PATH_SRC)/IceCast.cpp		\
			$(PATH_SRC)/Mysql.cpp		\
			$(PATH_SRC)/Proftpd.cpp		\
			$(PATH_SRC)/SQLiteWrapper.cpp	\
			$(PATH_SRC)/Select.cpp		\
			$(PATH_SRC)/Server.cpp		\
			$(PATH_SRC)/Signal.cpp		\
			$(PATH_SRC)/Socket.cpp		\
			$(PATH_SRC)/SocketClient.cpp	\
			$(PATH_SRC)/SocketServer.cpp	\
			$(PATH_SRC)/State.cpp		\
			$(PATH_SRC)/Stream.cpp		\
			$(PATH_SRC)/XmlParser.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXX		=	g++
RM		=	rm -f

INCLUDES	+=	-I$(PATH_INCLUDE) -I$(PATH_COMMON)
INCLUDES	+=	`pkg-config sqlite3 --cflags`
INCLUDES	+=	`xml2-config --cflags`

LIBRARIES	+=	-L$(PATH_LIBRARY)
LIBRARIES	+=	`pkg-config sqlite3 --libs`
LIBRARIES	+=	`xml2-config --libs`

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
