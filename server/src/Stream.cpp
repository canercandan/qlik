//
// Stream.cpp for server in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Oct 12 18:39:49 2008 caner candan
// Last update Sun Oct 12 18:53:43 2008 caner candan
//

#include "Stream.h"

Stream::Stream()
{}

Stream::~Stream()
{}

Stream::Stream(const Stream& stream)
{*this = stream;}

Stream&	Stream::operator=(const Stream& stream)
{
  if (this != &stream)
    {
      _name = stream._name;
      _slots = stream._slots;
      _bits = stream._bits;
      _title = stream._title;
      _port = stream._port;
    }
  return (*this);
}
