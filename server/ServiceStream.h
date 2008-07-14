//
// ServiceStream.h for ServiceStream in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 09:57:53 2008 caner candan
// Last update Mon Jul 14 22:47:38 2008 caner candan
//

#ifndef __SERVICESTREAM_H__
# define __SERVICESTREAM_H__

# include "Service.h"

class	ServiceStream : public Service
{
public:
  ServiceStream();
  ServiceStream(const ServiceStream&);
  ~ServiceStream();
  ServiceStream&	operator=(const ServiceStream&);
private:
};

#endif // !__SERVICESTREAM_H__
