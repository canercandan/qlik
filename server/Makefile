### Makefile --- 
## 
## Filename: Makefile
## Description: 
## Author: Caner Candan
## Maintainer: 
## Created: Sun Dec 28 10:33:20 2008 (+0200)
## Version: 
## Last-Updated: Sun Dec 28 10:33:50 2008 (+0200)
##           By: Caner Candan
##     Update #: 4
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

######################################################################
### Makefile ends here
