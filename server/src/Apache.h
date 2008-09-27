//
// Apache.h for Apache in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Sep  2 02:54:03 2008 caner candan
// Last update Tue Sep  2 14:24:49 2008 caner candan
//

#ifndef __APACHE_H__
# define __APACHE_H__

# include "IServerWeb.h"
# include "Client.h"

class	Apache : public IServerWeb
{
public:
  Apache(Client*);

  void	createHost(const std::string& domain);
private:
  void	_createRoot();
private:
  std::string	_user;
  std::string	_dirConfig;
  std::string	_dirUserConfig;
  std::string	_fileUserConfig;
  std::string	_rootDir;
};

#endif // !__APACHE_H__
