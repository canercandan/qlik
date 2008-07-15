//
// Service.cpp for Service in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 10:01:42 2008 caner candan
// Last update Tue Jul 15 13:35:50 2008 caner candan
//

#include "Service.h"

Service::Service(const std::string& name,
		 const std::string& passwd,
		 Type type /*= WEB*/)
  : _name(name), _passwd(passwd), _type(type)
{}

Service::Service(const Service& s)
{*this = s;}

Service::~Service()
{}

Service&	Service::operator=(const Service& s)
{
  if (this != &s)
    {
      this->_name = s._name;
      this->_passwd = s._passwd;
      this->_type = s._type;
    }
  return (*this);
}

const std::string&	Service::getPasswd(void) const
{
  return (this->_passwd);
}

const std::string&	Service::getName(void) const
{
  return (this->_name);
}

const Service::Type&	Service::getType(void) const
{
  return (this->_type);
}
