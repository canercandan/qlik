//
// Protocole.h for ekzay in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 16:29:02 2008 caner candan
// Last update Thu Oct 30 13:53:33 2008 caner candan
//

#ifndef __PROTOCOLE_H__
# define __PROTOCOLE_H__

# define PATTERN_NAME		"^[a-zA-Z0-9-_]+$"
# define PATTERN_DOMAIN		"^(www.)?[a-z0-9-_]+\\.[a-z]{2,4}$"
# define PATTERN_USERNAME	"^[a-zA-Z][a-zA-Z0-9-_]{3,19}$"
# define PATTERN_PASSWD		"^.{4,20}$"

# define NL	"\n"
# define SP	" "
# define EMPTY	""

# define OK	"ok"
# define KO	"ko"

# define BEGIN	"begin"
# define END	"end"

# define WELCOME	"welcome"

# define LOGIN	"login"
# define LOGOUT	"logout"
# define CREATE	"create"

# define CREDIT	"credit"

# define STATUS	"status"

# define CLIENTS	"clients"
# define ACCOUNTS	"accounts"
# define MESSAGE	"message"

# define WEB	"web"
# define STREAM	"stream"

# define WEB_DETAIL	"web_detail"
# define STREAM_DETAIL	"stream_detail"

# define OFFER_WEB	"offer_web"
# define OFFER_STREAM	"offer_stream"

# define CREATE_OFFER_WEB	"create_offer_web"
# define CREATE_OFFER_STREAM	"create_offer_stream"

# define CREATE_WEB	"create_web"
# define CREATE_STREAM	"create_stream"

# define NEWS		"news"
# define NEWS_DETAIL	"news_detail"

# define STREAM_STATUS	"stream_status"
# define STREAM_START	"stream_start"
# define STREAM_STOP	"stream_stop"

# define HALT	"halt"
# define BREAK	"break"
# define PLAY	"play"
# define RELOAD	"reload"

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
