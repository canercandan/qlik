######################################################################
# Automatically generated by qmake (2.01a) Tue Jul 15 15:07:39 2008
######################################################################

TEMPLATE	=	app
TARGET		=
DEPENDPATH	+=	.
INCLUDEPATH	+=	.

DEFINES		+=	#QT_NO_DEBUG_OUTPUT

# Input
HEADERS		+=	Client.h	\
			Connect.h	\
			Create.h	\
			Service.h	\
			Message.h	\
			Web.h		\
			Stream.h	\
			Credit.h	\
			Singleton.hpp	\
			State.h

FORMS		+=	Client.ui	\
			Connect.ui	\
			Create.ui	\
			Service.ui	\
			Message.ui	\
			Web.ui		\
			Stream.ui	\
			Credit.ui

SOURCES		+=	main.cpp	\
			Client.cpp	\
			Connect.cpp	\
			Create.cpp	\
			Service.cpp	\
			Message.cpp	\
			Web.cpp		\
			Stream.cpp	\
			Credit.cpp	\
			State.cpp

CONFIG		+=	debug

QT		+=	network		\
			sql
