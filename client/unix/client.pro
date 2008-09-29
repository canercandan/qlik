######################################################################
# Automatically generated by qmake (2.01a) Tue Jul 15 15:07:39 2008
######################################################################

TEMPLATE	=	app
TARGET		=
DEPENDPATH	+=	.
INCLUDEPATH	+=	. ../../common

DEFINES		+=	#QT_NO_DEBUG_OUTPUT

# Input
HEADERS		+=	../src/Accounts.h	\
			../src/Client.h		\
			../src/Connect.h	\
			../src/Contact.h	\
			../src/Create.h		\
			../src/Credit.h		\
			../src/Database.h	\
			../src/Message.h	\
			../src/Options.h	\
			../src/Service.h	\
			../src/Singleton.hpp	\
			../src/Socket.h		\
			../src/State.h		\
			../src/Stream.h		\
			../src/Web.h		\
			../../common/Protocole.h

FORMS		+=	../src/Accounts.ui	\
			../src/Client.ui	\
			../src/Connect.ui	\
			../src/Contact.ui	\
			../src/Create.ui	\
			../src/Credit.ui	\
			../src/Message.ui	\
			../src/Options.ui	\
			../src/Service.ui	\
			../src/Stream.ui	\
			../src/Web.ui

SOURCES		+=	../src/main.cpp		\
			../src/Accounts.cpp	\
			../src/Client.cpp	\
			../src/Connect.cpp	\
			../src/Contact.cpp	\
			../src/Create.cpp	\
			../src/Credit.cpp	\
			../src/Database.cpp	\
			../src/Message.cpp	\
			../src/Options.cpp	\
			../src/Service.cpp	\
			../src/Socket.cpp	\
			../src/State.cpp	\
			../src/Stream.cpp	\
			../src/Web.cpp

CONFIG		+=	#debug

QT		+=	network	\
			sql
