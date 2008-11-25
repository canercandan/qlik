##
## client.pro for client in /home/candan_c/cu/rendu/qlik/client
## 
## Made by caner candan
## Login   <candan_c@epitech.net>
## 
## Started on  Wed Nov 26 00:03:08 2008 caner candan
## Last update Wed Nov 26 00:14:09 2008 caner candan
##

TEMPLATE	=	app
TARGET		=	client

DEPENDPATH	+=	.
INCLUDEPATH	+=	. src ../../common/src

DESTDIR		+=	bin
MOD_DIR		+=	build/moc
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
