//
// ServiceWeb.cpp for ServiceWeb in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 10:01:42 2008 caner candan
// Last update Tue Jul 15 14:47:15 2008 caner candan
//

#include "ServiceWeb.h"

ServiceWeb::Offer	ServiceWeb::offers[NB_OFFERS_WEB] = {
  {100, 1},
  {200, 2},
  {300, 3},
  {400, 4}
};

ServiceWeb::ServiceWeb(const std::string& name,
		       const std::string& passwd,
		       const std::string& domain,
		       const ServiceWeb::OfferId& offerId /*= WEB100*/)
  : Service(name, passwd, Service::WEB),
    _domain(domain),
    _offerId(offerId >= NB_OFFERS_WEB
	     ? (OfferId)(NB_OFFERS_WEB - 1) : offerId)
{}

ServiceWeb::ServiceWeb(const ServiceWeb& s)
  : Service(s.getName(), s.getPasswd(), Service::WEB)
{*this = s;}

ServiceWeb::~ServiceWeb()
{}

ServiceWeb&	ServiceWeb::operator=(const ServiceWeb& s)
{
  if (this != &s)
    {
      this->_domain = s._domain;
      this->_offerId = s._offerId;
    }
  return (*this);
}

const std::string&	ServiceWeb::getDomain(void) const
{
  return (this->_domain);
}

const ServiceWeb::Offer&	ServiceWeb::getOffer(void) const
{
  return (offers[this->_offerId]);
}
