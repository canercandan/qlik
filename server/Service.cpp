//
// Service.cpp for Service in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 10:01:42 2008 caner candan
// Last update Sun Jul 13 10:04:28 2008 caner candan
//

#include "Service.h"

Service::Service(Type type /*= WEB*/)
  : _type(type)
{}

Service::Service(const Service& s)
{*this = s;}

Service::~Service()
{}

Service&	Service::operator=(const Service& s)
{
  if (this != &s)
    {
      this->_type = s._type;
    }
  return (*this);
}

const Service::Type&	Service::getType(void) const
{
  return (this->_type);
}
