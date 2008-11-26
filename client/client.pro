### client.pro --- 
## 
## Filename: client.pro
## Description: 
## Author: Caner Candan
## Maintainer: 
## Created: Thu Nov 27 01:11:01 2008 (+0200)
## Version: 
## Last-Updated: Thu Nov 27 01:11:18 2008 (+0200)
##           By: Caner Candan
##     Update #: 1
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

TEMPLATE	=	app
TARGET		=	client

DEPENDPATH	+=	.
INCLUDEPATH	+=	. src ../common/src

DESTDIR		+=	bin
MOC_DIR		+=	build/moc
RCC_DIR		+=	build/rcc
UI_DIR		+=	build/ui

RC_FILE		+=	client.rc
RESOURCES	+=	resources/resources.qrc

DEFINES		+=	#QT_NO_DEBUG_OUTPUT

FORMS		+=	ui/About.ui		\
			ui/Accounts.ui		\
			ui/AccountsAdmin.ui	\
			ui/Client.ui		\
			ui/Connect.ui		\
			ui/Contact.ui		\
			ui/Create.ui		\
			ui/Credit.ui		\
			ui/Lang.ui		\
			ui/Message.ui		\
			ui/News.ui		\
			ui/Options.ui		\
			ui/Service.ui		\
			ui/Stream.ui		\
			ui/Web.ui

HEADERS		+=	src/About.h		\
			src/Accounts.h		\
			src/AccountsAdmin.h	\
			src/Action.h		\
			src/Client.h		\
			src/Connect.h		\
			src/Contact.h		\
			src/Create.h		\
			src/Credit.h		\
			src/Database.h		\
			src/Lang.h		\
			src/Message.h		\
			src/News.h		\
			src/Options.h		\
			src/Service.h		\
			src/Singleton.hpp	\
			src/Socket.h		\
			src/State.h		\
			src/Stream.h		\
			src/Web.h		\
			../common/src/Protocole.h

SOURCES		+=	src/main.cpp		\
			src/About.cpp		\
			src/Accounts.cpp	\
			src/AccountsAdmin.cpp	\
			src/Action.cpp		\
			src/Client.cpp		\
			src/Connect.cpp		\
			src/Contact.cpp		\
			src/Create.cpp		\
			src/Credit.cpp		\
			src/Database.cpp	\
			src/Lang.cpp		\
			src/Message.cpp		\
			src/News.cpp		\
			src/Options.cpp		\
			src/Service.cpp		\
			src/Socket.cpp		\
			src/State.cpp		\
			src/Stream.cpp		\
			src/Web.cpp

TRANSLATIONS	+=	resources/translations/client_en_US.ts	\
			resources/translations/client_de.ts	\
			resources/translations/client_fr.ts

CONFIG		+=	qt warn_on release #debug

QT		+=	core gui network sql

macx {
OBJECTS_DIR	+=	build/o/mac
}

unix {
OBJECTS_DIR	+=	build/o/unix
}

win32 {
OBJECTS_DIR	+=	build/o/win32
}

######################################################################
### client.pro ends here
