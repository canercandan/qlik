//
// Service.h for Service in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 09:57:53 2008 caner candan
// Last update Mon Jul 14 22:49:24 2008 caner candan
//

#ifndef __SERVICE_H__
# define __SERVICE_H__

class	Service
{
public:
  enum	Type
    {
      WEB,
      STREAM
    };
public:
  Service(Type type = WEB);
  Service(const Service&);
  ~Service();
  Service&	operator=(const Service&);

  const Type&	getType(void) const;
private:
  Type	_type;
};

#endif // !__SERVICE_H__
