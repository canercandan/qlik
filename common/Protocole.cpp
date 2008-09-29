//
// Protocole.cpp for ekzay in /home/candan_c/cu/rendu/ekzay/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Sep 29 19:59:34 2008 caner candan
// Last update Mon Sep 29 20:08:14 2008 caner candan
//

#include "Protocole.h"

namespace	Protocole
{
  const char*	ok = "ok\n";
  const char*	ko = "ko\n";

  const char*	empty = "";

  const char*	begin = "begin\n";
  const char*	end = "end\n";

  const char*	welcome = "welcome\n";

  const char*	login = "login";
  const char*	logout = "logout";
  const char*	create = "create";

  const char*	credit = "credit";
  const char*	status = "status";
  const char*	clients = "clients";
  const char*	accounts = "accounts";
  const char*	message = "message";

  const char*	servicesWeb = "services_web";
  const char*	servicesStream = "services_stream";
  const char*	servicesWebDetail = "services_web_detail";
  const char*	servicesStreamDetail = "services_stream_detail";

  const char*	offerWeb = "offer_web";
  const char*	offerStream = "offer_stream";

  const char*	createOfferWeb = "create_offer_web";
  const char*	createOfferStream = "create_offer_stream";
  const char*	createWeb = "create_web";
  const char*	createStream = "create_stream";

  const char*	news = "news";
  const char*	newsDetail = "news_detail";

  const char*	streamStart = "stream_start";
  const char*	streamStop = "stream_stop";

  const int&	ratioWebSpace = 100;
  const int&	ratioWebDb = 1;
  const int&	ratioStreamSlot = 5;
  const int&	ratioStreamBits = 24;

  const char*	passwdCharacters =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "!\"#$%&'()*+,-./:;<=>?[\\]^_`{|}~";
  const int&		passwdSize = 8;
};
