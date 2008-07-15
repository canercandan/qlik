//
// Service.h for Service in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 09:57:53 2008 caner candan
// Last update Tue Jul 15 13:34:46 2008 caner candan
//

#ifndef __SERVICE_H__
# define __SERVICE_H__

# include <string>

class	Service
{
public:
  enum	Type
    {
      WEB,
      STREAM
    };
public:
  Service(const std::string& name,
	  const std::string& passwd,
	  Type type = WEB);
  Service(const Service&);
  ~Service();
  Service&	operator=(const Service&);

  const std::string&	getName(void) const;
  const std::string&	getPasswd(void) const;
  const Type&		getType(void) const;
private:
  std::string	_name;
  std::string	_passwd;
  Type		_type;
};

#endif // !__SERVICE_H__
