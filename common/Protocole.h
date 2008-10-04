//
// Protocole.h for ekzay in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 16:29:02 2008 caner candan
// Last update Sat Oct  4 15:30:27 2008 caner candan
//

#ifndef __PROTOCOLE_H__
# define __PROTOCOLE_H__

# define OK	"ok\n"
# define KO	"ko\n"

# define EMPTY	""

# define BEGIN	"begin\n"
# define END	"end\n"

# define WELCOME	"welcome\n"

# define LOGIN	"login"
// login USERNAME PASSWORD
// -> login (CREDIT|KO)

# define LOGOUT	"logout"
// logout
// -> logout OK

# define CREATE	"create"
// create USERNAME
// -> create (PASSWORD|KO)

# define CREDIT	"credit"
// credit
// -> credit CREDIT

# define STATUS	"status"
// status
// -> status (OK|KO)

# define CLIENTS	"clients"
// clients
// -> clients (BEGIN\n*(USERNAME)\nEND|KO)

# define ACCOUNTS	"accounts"
// accounts
// -> accounts (BEGIN\n*(USERNAME)\nEND|KO)

# define MESSAGE	"message"
// message USERNAME MESSAGE
// -> message (OK|KO)
// -> message FROM MESSAGE

# define SERVICES_WEB	"services_web"
// services_web
// -> services_web (BEGIN\n*(NAME)\nEND|KO)

# define SERVICES_STREAM	"services_stream"
// services_stream
// -> services_stream (BEGIN\n*(NAME)\nEND|KO)

# define SERVICES_WEB_DETAIL	"services_web_detail"
// services_web_detail ROW
// -> services_web_detail (NAME SPACE NB_DB DOMAIN
// CREATED EXPIRED|KO)

# define SERVICES_STREAM_DETAIL	"services_stream_detail"
// services_stream_detail ROW
// -> services_stream_detail (NAME SLOTS BITS TITLE
// CREATED EXPIRED|KO)

# define OFFER_WEB	"offer_web"
// offer_web
// -> offer_web (BEGIN\n*(PRICE NAME)\nEND|KO)

# define OFFER_STREAM	"offer_stream"
// offer_stream
// -> offer_stream (BEGIN\n*(PRICE NAME)\nEND|KO)

# define CREATE_OFFER_WEB	"create_offer_web"
// create_offer_web NAME ROW DOMAIN
// -> create_offer_web (OK|KO)

# define CREATE_OFFER_STREAM	"create_offer_stream"
// create_offer_stream NAME ROW TITLE
// -> create_offer_stream (OK|KO)

# define CREATE_WEB	"create_web"
// create_web NAME SPACE NB_DB DOMAIN
// -> create_web (OK|KO)

# define CREATE_STREAM	"create_stream"
// create_stream NAME SLOTS BITS TITLE
// -> create_stream (OK|KO)

# define NEWS	"news"
// news
// -> news (BEGIN\n*(DATE SUBJECT)\nEND|KO)

# define NEWS_DETAIL	"news_detail"
// news_detail ROW
// -> news_detail (BODY|KO)

# define STREAM_START	"stream_start"
// stream_start NAME
// -> stream_start (OK|KO)

# define STREAM_STOP	"stream_stop"
// stream_stop NAME
// -> stream_stop (OK|KO)

# define RATIO_WEB_SPACE	100
# define RATIO_WEB_DB		1
# define RATIO_STREAM_SLOT	5
# define RATIO_STREAM_BITS	24

# define PASSWD_CHARACTERS			\
  "abcdefghijklmnopqrstuvwxyz"			\
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"			\
  "0123456789"					\
  "!\"#$%&'()*+,-./:;<=>?[\\]^_`{|}~"

# define PASSWD_SIZE	8

#endif // !__PROTOCOLE_H__
