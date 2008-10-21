//
// IServerStream.cpp for IServerStream in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Sep  2 02:17:58 2008 caner candan
// Last update Sun Oct 12 18:53:59 2008 caner candan
//

#ifndef __ISERVERSTREAM_H__
# define __ISERVERSTREAM_H__

# include <string>

class	IServerStream
{
public:
  virtual ~IServerStream(){}

  virtual void	createStream() = 0;
};

#endif // !__ISERVERSTREAM_H__
