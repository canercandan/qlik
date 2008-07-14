//
// ServiceWeb.h for ServiceWeb in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 09:57:53 2008 caner candan
// Last update Mon Jul 14 22:44:55 2008 caner candan
//

#ifndef __SERVICEWEB_H__
# define __SERVICEWEB_H__

# include "Service.h"

class	ServiceWeb : public Service
{
public:
  ServiceWeb();
  ServiceWeb(const ServiceWeb&);
  ~ServiceWeb();
  ServiceWeb&	operator=(const ServiceWeb&);
private:
};

#endif // !__SERVICEWEB_H__
