//
// Protocole.h for ekzay in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 16:29:02 2008 caner candan
// Last update Mon Sep 29 20:03:00 2008 caner candan
//

#ifndef __PROTOCOLE_H__
# define __PROTOCOLE_H__

# include <string>

namespace	Protocole
{
  const char*	ok;
  const char*	ko;

  const char*	empty;

  const char*	begin;
  const char*	end;

  const char*	welcome;

  const char*	login;
  // login USERNAME PASSWORD
  // -> login (CREDIT|KO)

  const char*	logout;
  // logout
  // -> logout OK

  const char*	create;
  // create USERNAME
  // -> create (PASSWORD|KO)

  const char*	credit;
  // credit
  // -> credit CREDIT

  const char*	status;
  // status
  // -> status (OK|KO)

  const char*	clients;
  // clients
  // -> clients (BEGIN\n*(USERNAME)\nEND|KO)

  const char*	accounts;
  // accounts
  // -> accounts (BEGIN\n*(USERNAME)\nEND|KO)

  const char*	message;
  // message USERNAME MESSAGE
  // -> message (OK|KO)
  // -> message FROM MESSAGE

  const char*	servicesWeb;
  // services_web
  // -> services_web (BEGIN\n*(NAME)\nEND|KO)

  const char*	servicesStream;
  // services_stream
  // -> services_stream (BEGIN\n*(NAME)\nEND|KO)

  const char*	servicesWebDetail;
  // services_web_detail ROW
  // -> services_web_detail (NAME SPACE NB_DB DOMAIN
  // CREATED EXPIRED|KO)

  const char*	servicesStreamDetail;
  // services_stream_detail ROW
  // -> services_stream_detail (NAME SLOTS BITS TITLE
  // CREATED EXPIRED|KO)

  const char*	offerWeb;
  // offer_web
  // -> offer_web (BEGIN\n*(PRICE NAME)\nEND|KO)

  const char*	offerStream;
  // offer_stream
  // -> offer_stream (BEGIN\n*(PRICE NAME)\nEND|KO)

  const char*	createOfferWeb;
  // create_offer_web NAME ROW DOMAIN
  // -> create_offer_web (OK|KO)

  const char*	createOfferStream;
  // create_offer_stream NAME ROW TITLE
  // -> create_offer_stream (OK|KO)

  const char*	createWeb;
  // create_web NAME SPACE NB_DB DOMAIN
  // -> create_web (OK|KO)

  const char*	createStream;
  // create_stream NAME SLOTS BITS TITLE
  // -> create_stream (OK|KO)

  const char*	news;
  // news
  // -> news (BEGIN\n*(DATE SUBJECT)\nEND|KO)

  const char*	newsDetail;
  // news_detail ROW
  // -> news_detail (BODY|KO)

  const char*	streamStart;
  // stream_start NAME
  // -> stream_start (OK|KO)

  const char*	streamStop;
  // stream_stop NAME
  // -> stream_stop (OK|KO)

  const int&	ratioWebSpace;
  const int&	ratioWebDb;
  const int&	ratioStreamSlot;
  const int&	ratioStreamBits;

  const char*	passwdCharacters;
  const int&	passwdSize;
};

#endif // !__PROTOCOLE_H__
