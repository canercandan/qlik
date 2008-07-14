//
// ServiceWeb.cpp for ServiceWeb in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 10:01:42 2008 caner candan
// Last update Mon Jul 14 22:50:03 2008 caner candan
//

#include "ServiceWeb.h"

ServiceWeb::ServiceWeb()
  : Service(Service::WEB)
{}

ServiceWeb::ServiceWeb(const ServiceWeb& s)
  : Service(Service::WEB)
{*this = s;}

ServiceWeb::~ServiceWeb()
{}

ServiceWeb&	ServiceWeb::operator=(const ServiceWeb& s)
{
  if (this != &s)
    {}
  return (*this);
}
