// Protocole.h --- 
// 
// Filename: Protocole.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:22:14 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:22:18 2008 (+0200)
//           By: Caner Candan
//     Update #: 1
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.

// 
// 

// Code:

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
# define RIGHT	"right"

# define CLIENTS	"clients"

# define ACCOUNTS		"accounts"
# define ACCOUNTS_MODIFY	"accounts_modify"

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
# define NEWS_ADD	"news_add"
# define NEWS_DELETE	"news_delete"

# define WEB_STATUS	"web_status"
# define WEB_START	"web_start"
# define WEB_STOP	"web_stop"

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

# define RIGHT_NONE		0
# define RIGHT_MESSAGE		1 << 0
# define RIGHT_WEB		1 << 1
# define RIGHT_STREAM		1 << 2
# define RIGHT_NEWS		1 << 3
# define RIGHT_SERVER		1 << 4
# define RIGHT_ADMIN		1 << 5

# define PASSWD_CHARACTERS			\
  "abcdefghijklmnopqrstuvwxyz"			\
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"			\
  "0123456789"					\
  "!\"#$%&'()*+,-./:;<=>?[\\]^_`{|}~"

# define PASSWD_SIZE	8

#endif // !__PROTOCOLE_H__

// 
// Protocole.h ends here
