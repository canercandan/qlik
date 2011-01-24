// Apache.cpp --- 
// 
// Filename: Apache.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:44:20 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:44:23 2008 (+0200)
//           By: Caner Candan
//     Update #: 1
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.

// 
// 

// Code:

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
  char	root[128];

  ::mkdir(_dirConfig.c_str(), 0755);
  ::getcwd(root, sizeof(root));
  _rootDir.append(root);
  _createRoot();
}

void	Apache::_createRoot()
{
  std::ofstream	out(_fileUserConfig.c_str());

  out << "Include "
      << _rootDir << '/'
      << _dirUserConfig << "/*.conf"
      << std::endl;
  out.close();
  ::mkdir(_dirUserConfig.c_str(), 0755);
}

void	Apache::createHost(const std::string& domain)
{
  std::string	configFile(_dirUserConfig + '/'
			   + domain + ".conf");
  std::string	wwwPath("/home/web_1/web/vhosts/"
			+ _user + '/' + domain);
  std::ofstream	out(configFile.c_str());

  out << "# user: " << _user << " domain: " << domain
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
      << "# user: " << _user << " domain: " << domain
      << " configuration end" << std::endl;
  out.close();
}

// 
// Apache.cpp ends here
