### Makefile --- 
## 
## Filename: Makefile
## Description: 
## Author: Caner Candan
## Maintainer: 
## Created: Thu Nov 27 01:43:52 2008 (+0200)
## Version: 
## Last-Updated: Sat Nov 29 12:33:27 2008 (+0200)
##           By: Caner Candan
##     Update #: 18
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
## 27-Nov-2008    Caner Candan  
##    Last-Updated: Thu Nov 27 12:02:36 2008 (+0200) #5 (Caner Candan)
##    ../src -> src, . -> bin, mkdir bin if not exist
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
			-@$(MKDIR) $(PATH_BIN)
			$(CXX) -o $@ $(OBJS) $(LDFLAGS)

all		:	$(NAME)

clean		:
			-$(RM) $(PATH_SRC)/*~
			-$(RM) $(PATH_SRC)/*.o
			-$(RM) *.core

fclean		:	clean
			-$(RM) $(NAME)
			-$(RM) -r $(PATH_BIN)

re		:	fclean all

.PHONY		:	all clean fclean re

.cpp.o		:
			$(CXX) $(CFLAGS) -c $< -o $@

######################################################################
### Makefile ends here
