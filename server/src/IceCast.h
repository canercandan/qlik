//
// IceCast.h for IceCast in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Sep  2 14:04:49 2008 caner candan
// Last update Sun Oct 12 19:04:56 2008 caner candan
//

#ifndef __ICECAST_H__
# define __ICECAST_H__

# include "IServerStream.h"
# include "Stream.h"

class	IceCast : public IServerStream
{
public:
  IceCast(Stream&);

  void	createStream();
private:
  void	_createRoot();
private:
  Stream&	_stream;
  std::string	_user;
  std::string	_dirConfig;
  std::string	_dirUserConfig;
  std::string	_rootDir;
};

#endif // !__ICECAST_H__
