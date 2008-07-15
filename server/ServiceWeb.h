//
// ServiceWeb.h for ServiceWeb in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 09:57:53 2008 caner candan
// Last update Tue Jul 15 14:48:11 2008 caner candan
//

#ifndef __SERVICEWEB_H__
# define __SERVICEWEB_H__

# include <string>
# include "Service.h"

# define NB_OFFERS_WEB	4

class	ServiceWeb : public Service
{
public:
  enum	OfferId
    {
      WEB100,
      WEB200,
      WEB300,
      WEB400
    };

  struct	Offer
  {
    int		space;
    int		nbDb;
  };

  static Offer	offers[NB_OFFERS_WEB];
public:
  ServiceWeb(const std::string& name,
	     const std::string& passwd,
	     const std::string& domain,
	     const OfferId& offerId = WEB100);
  ServiceWeb(const ServiceWeb&);
  ~ServiceWeb();
  ServiceWeb&	operator=(const ServiceWeb&);

  const std::string&	getDomain(void) const;
  const Offer&		getOffer(void) const;
private:
  std::string	_domain;
  OfferId	_offerId;
};

#endif // !__SERVICEWEB_H__
