### Makefile --- 
## 
## Filename: Makefile
## Description: 
## Author: Caner Candan
## Maintainer: 
## Created: Sun Dec 28 11:58:17 2008 (+0200)
## Version: 
## Last-Updated: Sun Dec 28 12:21:23 2008 (+0200)
##           By: Caner Candan
##     Update #: 27
## URL: 
## Keywords: 
## Compatibility: 
## 
######################################################################
## 
### Commentary: 
## 
## 
## 
######################################################################
## 
### Change log:
## 
## 
######################################################################
## 
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License as
## published by the Free Software Foundation; either version 3, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program; see the file COPYING.  If not, write to
## the Free Software Foundation, Inc., 51 Franklin Street, Fifth
## Floor, Boston, MA 02110-1301, USA.
## 
######################################################################
## 
### Code:

PATH_BIN	=	bin
PATH_SRC	=	src
PATH_INCLUDE	=	.
PATH_LIBRARY	=	.
PATH_COMMON	=	../common/src

NAME		=	$(PATH_BIN)/server

SRCS		=	\
			$(PATH_SRC)/main.cpp		\
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
			$(PATH_SRC)/Service.cpp		\
			$(PATH_SRC)/Signal.cpp		\
			$(PATH_SRC)/Socket.cpp		\
			$(PATH_SRC)/SocketClient.cpp	\
			$(PATH_SRC)/SocketServer.cpp	\
			$(PATH_SRC)/State.cpp		\
			$(PATH_SRC)/Stream.cpp		\
			$(PATH_SRC)/XmlParser.cpp	\
			$(PATH_SRC)/Web.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXX		=	g++
RM		=	rm -f
MKDIR		=	mkdir -p
ECHO		=	echo
ECHOE		=	echo -e
ECHON		=	echo -n

SUCCESS		=	$(ECHOE) "[\033[32mSUCCESS\033[0m] "
FAILED		=	$(ECHOE) "[\033[31mFAILED\033[0m] "

INCLUDES	+=	-I$(PATH_INCLUDE) -I$(PATH_COMMON)
INCLUDES	+=	`pkg-config sqlite3 --cflags`
INCLUDES	+=	`xml2-config --cflags`

LIBRARIES	+=	-L$(PATH_LIBRARY)
LIBRARIES	+=	`pkg-config sqlite3 --libs`
LIBRARIES	+=	`xml2-config --libs`

DEBUG_TRUE	=	-g -DDEBUG
COMPAT		+=	-D__BSD_VISIBLE
WARNINGS	+=	-W -Wall -Werror

CFLAGS		+=	$(INCLUDES) $(DEBUG_$(DEBUG)) $(COMPAT) $(WARNINGS)
LDFLAGS		+=	$(LIBRARIES)

.SUFFIXES	:	.cpp.o

$(NAME)		:	$(OBJS)
			-@$(ECHON) "*** Making directory $(PATH_BIN) "
			-@$(MKDIR) $(PATH_BIN) && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Compiling $(OBJS) to $@ "
			-@$(CXX) -o $@ $(OBJS) $(LDFLAGS) && $(SUCCESS) || $(FAILED)

all		:	$(NAME)

clean		:
			-@$(ECHON) "*** Removing $(PATH_SRC)/*~ "
			-@$(RM) $(PATH_SRC)/*~ && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Removing $(PATH_SRC)/*.o "
			-@$(RM) $(PATH_SRC)/*.o && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Removing $(PATH_BIN)/*.core "
			-@$(RM) $(PATH_BIN)/*.core && $(SUCCESS) || $(FAILED)

fclean		:	clean
			-@$(ECHON) "*** Removing $(NAME) "
			-@$(RM) $(NAME) && $(SUCCESS) || $(FAILED)

re		:	fclean all

.PHONY		:	all clean fclean re

.cpp.o		:
			-@$(ECHON) "*** Compiling $< to $@ "
			-@$(CXX) $(CFLAGS) -c $< -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/main.o	:	\
				$(PATH_SRC)/main.cpp	\
				$(PATH_SRC)/Server.h	\
				$(PATH_SRC)/Config.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/main.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/main.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Action.o	:	\
				$(PATH_SRC)/Action.cpp		\
				$(PATH_SRC)/Action.h		\
				$(PATH_COMMON)/Protocole.h	\
				$(PATH_SRC)/Database.h		\
				$(PATH_SRC)/Credit.h		\
				$(PATH_SRC)/Apache.h		\
				$(PATH_SRC)/IceCast.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Action.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Action.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Apache.o	:	\
				$(PATH_SRC)/Apache.cpp	\
				$(PATH_SRC)/Apache.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Apache.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Apache.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Client.o	:	\
				$(PATH_SRC)/Client.cpp	\
				$(PATH_SRC)/Client.h	\
				$(PATH_SRC)/Database.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Client.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Client.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Config.o	:	\
				$(PATH_SRC)/Config.cpp	\
				$(PATH_SRC)/Config.h	\
				$(PATH_SRC)/XmlParser.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Config.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Config.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Credit.o	:	\
				$(PATH_SRC)/Credit.cpp	\
				$(PATH_SRC)/Credit.h	\
				$(PATH_SRC)/Database.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Credit.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Credit.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Database.o	:	\
				$(PATH_SRC)/Database.cpp	\
				$(PATH_SRC)/Database.h		\
				$(PATH_SRC)/Config.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Database.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Database.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/IceCast.o	:	\
				$(PATH_SRC)/IceCast.cpp	\
				$(PATH_SRC)/IceCast.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/IceCast.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/IceCast.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Mysql.o	:	\
				$(PATH_SRC)/Mysql.cpp	\
				$(PATH_SRC)/Mysql.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Mysql.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Mysql.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Proftpd.o	:	\
				$(PATH_SRC)/Proftpd.cpp	\
				$(PATH_SRC)/Proftpd.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Proftpd.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Proftpd.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/SQLiteWrapper.o	:	\
				$(PATH_SRC)/SQLiteWrapper.cpp	\
				$(PATH_SRC)/SQLiteWrapper.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/SQLiteWrapper.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/SQLiteWrapper.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Select.o	:	\
				$(PATH_SRC)/Select.cpp		\
				$(PATH_SRC)/Select.h		\
				$(PATH_SRC)/Config.h		\
				$(PATH_SRC)/SocketServer.h	\
				$(PATH_SRC)/SocketClient.h	\
				$(PATH_SRC)/State.h		\
				$(PATH_COMMON)/Protocole.h	\
				$(PATH_SRC)/Action.h		\
				$(PATH_SRC)/Signal.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Select.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Select.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Server.o	:	\
				$(PATH_SRC)/Server.cpp	\
				$(PATH_SRC)/Server.h	\
				$(PATH_SRC)/Client.h	\
				$(PATH_SRC)/Signal.h	\
				$(PATH_SRC)/Config.h	\
				$(PATH_SRC)/Select.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Server.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Server.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Service.o	:	\
				$(PATH_SRC)/Service.cpp	\
				$(PATH_SRC)/Service.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Service.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Service.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Signal.o	:	\
				$(PATH_SRC)/Signal.cpp	\
				$(PATH_SRC)/Signal.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Signal.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Signal.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Socket.o	:	\
				$(PATH_SRC)/Socket.cpp	\
				$(PATH_SRC)/Socket.h	\
				$(PATH_SRC)/Config.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Socket.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Socket.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/SocketClient.o	:	\
				$(PATH_SRC)/SocketClient.cpp	\
				$(PATH_SRC)/SocketClient.h	\
				$(PATH_SRC)/State.h		\
				$(PATH_SRC)/Config.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/SocketClient.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/SocketClient.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/SocketServer.o	:	\
				$(PATH_SRC)/SocketServer.cpp	\
				$(PATH_SRC)/SocketServer.h	\
				$(PATH_SRC)/State.h		\
				$(PATH_SRC)/Config.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/SocketServer.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/SocketServer.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/State.o	:	\
				$(PATH_SRC)/State.cpp	\
				$(PATH_SRC)/State.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/State.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/State.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Stream.o	:	\
				$(PATH_SRC)/Stream.cpp	\
				$(PATH_SRC)/Stream.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Stream.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Stream.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/Web.o	:	\
				$(PATH_SRC)/Web.cpp	\
				$(PATH_SRC)/Web.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/Web.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/Web.cpp -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/XmlParser.o	:	\
				$(PATH_SRC)/XmlParser.cpp	\
				$(PATH_SRC)/XmlParser.h
				-@$(ECHON) "*** Compiling $(PATH_SRC)/XmlParser.cpp to $@ "
				-@$(CXX) $(CFLAGS) -c $(PATH_SRC)/XmlParser.cpp -o $@ && $(SUCCESS) || $(FAILED)

######################################################################
### Makefile ends here
