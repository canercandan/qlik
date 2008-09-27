//
// Apache.cpp for Apache in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Sep  2 03:47:39 2008 caner candan
// Last update Tue Sep  2 14:28:42 2008 caner candan
//

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include "Apache.h"

Apache::Apache(Client* client)
  : _user(client->getLogin()),
    _dirConfig("apache/"),
    _dirUserConfig(_dirConfig + _user),
    _fileUserConfig(_dirUserConfig + ".conf")
{
  char		root[128];

  ::mkdir(_dirConfig.c_str(), 0755);
  ::getcwd(root, sizeof(root));
  _rootDir.append(root);
  _createRoot();
}

void	Apache::_createRoot()
{
  std::ofstream	out(this->_fileUserConfig.c_str());

  out << "Include "
      << this->_rootDir << '/'
      << this->_dirUserConfig << "/*.conf"
      << std::endl;
  out.close();
  ::mkdir(this->_dirUserConfig.c_str(), 0755);
}

void	Apache::createHost(const std::string& domain)
{
  std::string	configFile(this->_dirUserConfig + '/'
			   + domain + ".conf");
  std::string	wwwPath("/home/web_1/web/vhosts/"
			+ this->_user + '/' + domain);
  std::ofstream	out(configFile.c_str());

  out << "# user: " << this->_user << " domain: " << domain
      << " configuration start" << std::endl
      << "<VirtualHost *>" << std::endl
      << "DocumentRoot " << wwwPath << "/www" << std::endl
      << "ServerDomain " << domain << std::endl
      << "ServerAlias www." << domain << std::endl
      << "CustomLog " << wwwPath
      << "/_log/www-access.log combined" << std::endl
      << "ErrorLog " << wwwPath
      << "/_log/www-error.log" << std::endl
      << "php_admin_value open_basedir \"" << wwwPath
      << "/www:" << wwwPath << "/_tmp\"" << std::endl
      << "php_admin_value upload_tmp_dir \"" << wwwPath
      << "/_tmp\"" << std::endl
      << "<Directory \"" << wwwPath << "/www\">" << std::endl
      << "Options Indexes FollowSymLinks" << std::endl
      << "AllowOverride All" << std::endl
      << "Order allow,deny" << std::endl
      << "Allow from all" << std::endl
      << "</Directory>" << std::endl
      << "</VirtualHost>" << std::endl
      << "# user: " << this->_user << " domain: " << domain
      << " configuration end" << std::endl;
  out.close();
}
