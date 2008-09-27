//
// IServerWeb.cpp for IServerWeb in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Sep  2 02:17:58 2008 caner candan
// Last update Tue Sep  2 08:48:29 2008 caner candan
//

#ifndef __ISERVERWEB_H__
# define __ISERVERWEB_H__

# include <string>

class	IServerWeb
{
public:
  virtual ~IServerWeb(){}

  virtual void	createHost(const std::string& domain) = 0;
};

#endif // !__ISERVERWEB_H__
