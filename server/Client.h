//
// Client.h for Client in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 08:50:46 2008 caner candan
// Last update Mon Sep  1 21:12:24 2008 caner candan
//

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <string>
# include "Socket.h"

class	Client
{
public:
  enum	Type
    {
      SERVER,
      CLIENT
    };

  enum	Right
    {
      USER,
      ADMIN
    };
public:
  Client(Socket *socket = NULL, Type type = SERVER);
  Client(const Client&);
  ~Client();
  Client&	operator=(const Client&);

  Socket		*getSocket(void) const;
  const std::string&	getBufRead(void) const;
  const std::string&	getBufWrite(void) const;
  const Type&		getType(void) const;
  const Right&		getRight(void) const;
  const std::string&	getLogin(void) const;
  int			getId(void) const;
  int			getCredit(void) const;

  bool	isConnected() const;

  void	appendBufRead(const std::string&);
  void	appendBufRead(const int&);

  void	appendBufWrite(const std::string&);
  void	appendBufWrite(const int&);

  void	setLogin(const std::string&);
  void	setId(const int&);
  void	setCredit(const int&);

  void	clearBufRead(void);
  void	clearBufWrite(void);
private:
  Socket	*_socket;
  std::string	_bufRead;
  std::string	_bufWrite;
  Type		_type;
  Right		_right;
  int		_id;
  std::string	_login;
  int		_credit;
};

#endif // !__CLIENT_H__
