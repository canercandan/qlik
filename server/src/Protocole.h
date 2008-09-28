//
// Protocole.h for server in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 16:29:02 2008 caner candan
// Last update Sun Sep 28 16:40:21 2008 caner candan
//

#ifndef __PROTOCOLE_H__
# define __PROTOCOLE_H__

# include <string>

namespace	Protocole
{
  const std::string&	ok = "ok\n";
  const std::string&	ko = "ko\n";

  const std::string&	empty = "";

  const std::string&	begin = "begin\n";
  const std::string&	end = "end\n";

  const std::string&	welcome = "welcome\n";

  const std::string&	login = "login";
  // login USERNAME PASSWORD
  // -> login (CREDIT|KO)

  const std::string&	logout = "logout";
  // logout
  // -> logout OK

  const std::string&	create = "create";
  // create USERNAME
  // -> create (PASSWORD|KO)

  const std::string&	credit = "credit";
  // credit
  // -> credit CREDIT

  const std::string&	status = "status";
  // status
  // -> status (OK|KO)

  const std::string&	clients = "clients";
  // clients
  // -> clients (BEGIN\n*(USERNAME)\nEND|KO)

  const std::string&	accounts = "accounts";
  // accounts
  // -> accounts (BEGIN\n*(USERNAME)\nEND|KO)

  const std::string&	message = "message";
  // message USERNAME MESSAGE
  // -> message (OK|KO)
  // -> message FROM MESSAGE

  const std::string&	servicesWeb = "services_web";
  // services_web
  // -> services_web (BEGIN\n*(NAME)\nEND|KO)

  const std::string&	servicesStream = "services_stream";
  // services_stream
  // -> services_stream (BEGIN\n*(NAME)\nEND|KO)

  const std::string&	servicesWebDetail = "services_web_detail";
  // services_web_detail ROW
  // -> services_web_detail (NAME SPACE NB_DB DOMAIN
  // CREATED EXPIRED|KO)

  const std::string&	servicesStreamDetail = "services_stream_detail";
  // services_stream_detail ROW
  // -> services_stream_detail (NAME SLOTS BITS TITLE
  // CREATED EXPIRED|KO)

  const std::string&	offerWeb = "offer_web";
  // offer_web
  // -> offer_web (BEGIN\n*(PRICE NAME)\nEND|KO)

  const std::string&	offerStream = "offer_stream";
  // offer_stream
  // -> offer_stream (BEGIN\n*(PRICE NAME)\nEND|KO)

  const std::string&	createOfferWeb = "create_offer_web";
  // create_offer_web NAME ROW DOMAIN
  // -> create_offer_web (OK|KO)

  const std::string&	createOfferStream = "create_offer_stream";
  // create_offer_stream NAME ROW TITLE
  // -> create_offer_stream (OK|KO)

  const std::string&	createWeb = "create_web";
  // create_web NAME SPACE NB_DB DOMAIN
  // -> create_web (OK|KO)

  const std::string&	createStream = "create_stream";
  // create_stream NAME SLOTS BITS TITLE
  // -> create_stream (OK|KO)

  const std::string&	news = "news";
  // news
  // -> news (BEGIN\n*(DATE SUBJECT)\nEND|KO)

  const std::string&	newsDetail = "news_detail";
  // news_detail ROW
  // -> news_detail (BODY|KO)

  const std::string&	streamStart = "stream_start";
  // stream_start NAME
  // -> stream_start (OK|KO)

  const std::string&	streamStop = "stream_stop";
  // stream_stop NAME
  // -> stream_stop (OK|KO)

  const int&	ratioWebSpace = 100;
  const int&	ratioWebDb = 1;
  const int&	ratioStreamSlot = 5;
  const int&	ratioStreamBits = 24;
};

#endif // !__PROTOCOLE_H__
