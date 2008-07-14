//
// ServiceStream.cpp for ServiceStream in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Jul 13 10:01:42 2008 caner candan
// Last update Mon Jul 14 22:50:18 2008 caner candan
//

#include "ServiceStream.h"

ServiceStream::ServiceStream()
  : Service(Service::STREAM)
{}

ServiceStream::ServiceStream(const ServiceStream& s)
  : Service(Service::STREAM)
{*this = s;}

ServiceStream::~ServiceStream()
{}

ServiceStream&	ServiceStream::operator=(const ServiceStream& s)
{
  if (this != &s)
    {}
  return (*this);
}
