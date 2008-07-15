//
// ServiceStream.h for ServiceStream in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 09:57:53 2008 caner candan
// Last update Tue Jul 15 13:38:44 2008 caner candan
//

#ifndef __SERVICESTREAM_H__
# define __SERVICESTREAM_H__

# include <string>
# include "Service.h"

# define NB_OFFERS_STREAM	4

class	ServiceStream : public Service
{
public:
  enum	OfferId
    {
      STRM05,
      STRM10,
      STRM15,
      STRM20
    };

  struct	Offer
  {
    int		slots;
    int		nbBits;
  };

  static Offer	offers[NB_OFFERS_STREAM];
public:
  ServiceStream(const std::string& name,
		const std::string& passwd,
		const OfferId& offerId = STRM05);
  ServiceStream(const ServiceStream&);
  ~ServiceStream();
  ServiceStream&	operator=(const ServiceStream&);

  const Offer&	getOffer(void) const;
private:
  OfferId	_offerId;
};

#endif // !__SERVICESTREAM_H__
