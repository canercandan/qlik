//
// ServiceStream.cpp for ServiceStream in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 10:01:42 2008 caner candan
// Last update Tue Jul 15 13:37:59 2008 caner candan
//

#include "ServiceStream.h"

ServiceStream::Offer	ServiceStream::offers[NB_OFFERS_STREAM] = {
  {5, 24},
  {10, 32},
  {15, 64},
  {20, 128}
};

ServiceStream::ServiceStream(const std::string& name,
			     const std::string& passwd,
			     const ServiceStream::OfferId& offerId /*= STRM05*/)
  : Service(name, passwd, Service::STREAM),
    _offerId(offerId >= NB_OFFERS_STREAM
	     ? (OfferId)(NB_OFFERS_STREAM - 1) : offerId)
{}

ServiceStream::ServiceStream(const ServiceStream& s)
  : Service(s.getName(), s.getPasswd(), Service::STREAM)
{*this = s;}

ServiceStream::~ServiceStream()
{}

ServiceStream&	ServiceStream::operator=(const ServiceStream& s)
{
  if (this != &s)
    {
      this->_offerId = s._offerId;
    }
  return (*this);
}

const ServiceStream::Offer&	ServiceStream::getOffer(void) const
{
  return (offers[this->_offerId]);
}
