//
// IceCast.cpp for IceCast in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Sep  2 14:07:57 2008 caner candan
// Last update Fri Sep  5 19:04:26 2008 caner candan
//

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include "IceCast.h"

IceCast::IceCast(Client* client)
  : _user(client->getLogin()),
    _dirConfig("icecast/"),
    _dirUserConfig(_dirConfig + _user)
{
  char	root[128];

  ::mkdir(_dirConfig.c_str(), 0755);
  ::getcwd(root, sizeof(root));
  _rootDir.append(root);
  _createRoot();
}

void	IceCast::_createRoot()
{
  ::mkdir(this->_dirUserConfig.c_str(), 0755);
}

void	IceCast::createStream(const std::string& name,
			      const int& slots,
			      const int& bits)
{
  std::string	configDir(this->_dirUserConfig + '/'
			  + name + '/');
  std::string	configFile(configDir + "icecast.xml");

  ::mkdir(configDir.c_str(), 0755);

  std::ofstream	out(configFile.c_str());
  const int&	port = 1234;

  out << "<icecast>" << std::endl
      << "<limits>" << std::endl
      << "<sources>2</sources>" << std::endl
      << "<clients>" << slots << "</clients>" << std::endl
      << "<burst-size>" << bits * 1024 << "</burst-size>" << std::endl
      << "</limits>" << std::endl
      << "<authentication>" << std::endl
      << "<source-password>" << name << "</source-password>" << std::endl
      << "<relay-password>" << name << "</relay-password>" << std::endl
      << "<admin-user>admin</admin-user>" << std::endl
      << "<admin-password>" << name << "</admin-password>" << std::endl
      << "</authentication>" << std::endl
      << "<directory>" << std::endl
      << "<yp-url-timeout>15</yp-url-timeout>" << std::endl
      << "<yp-url>http://dir.xiph.org/cgi-bin/yp-cgi</yp-url>" << std::endl
      << "</directory>" << std::endl
      << "<hostname>localhost</hostname>" << std::endl
      << "<listen-socket><port>" << port << "</port>"
      << "</listen-socket>" << std::endl
      << "<fileserve>1</fileserve>" << std::endl
      << "<paths>" << std::endl
      << "<logdir>" << this->_rootDir << '/' << configDir
      << "</logdir>" << std::endl
      << "<webroot>/usr/local/share/icecast/web</webroot>" << std::endl
      << "<adminroot>/usr/local/share/icecast/admin</adminroot>" << std::endl
      << "<alias source=\"/\" dest=\"/status.xsl\"/>" << std::endl
      << "</paths>" << std::endl
      << "<logging>" << std::endl
      << "<accesslog>access.log</accesslog>" << std::endl
      << "<errorlog>error.log</errorlog>" << std::endl
      << "<loglevel>3</loglevel>" << std::endl
      << "</logging>" << std::endl
      << "</icecast>" << std::endl;
  out.close();
}
