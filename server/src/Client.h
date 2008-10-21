//
// Client.h for Client in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 08:50:46 2008 caner candan
// Last update Thu Oct  9 19:25:26 2008 caner candan
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
  Client(Socket* socket = NULL, Type type = SERVER);
  Client(const Client&);
  ~Client();
  Client&	operator=(const Client&);

  Socket*		getSocket(void) const;
  const std::string&	getBufRead(void) const;
  const std::string&	getBufWrite(void) const;
  const Right&		getRight(void) const;

  bool	isConnected();

  void	appendBufRead(const std::string&);
  void	appendBufRead(const int&);

  void	appendBufWrite(const std::string&);
  void	appendBufWrite(const int&);

private:
  Socket*	_socket;
  std::string	_bufRead;
  std::string	_bufWrite;

public:
  const Type&	getType(void){return (_type);}
  void	setType(const Type& type){_type = type;}
private:
  Type	_type;

public:
  const Right&	getRight(void){return (_right);}
  void	setRight(const Right& right){_right = right;}
private:
  Right	_right;

public:
  const std::string&	getLogin(void){return (_login);}
  void	setLogin(const std::string& login){_login = login;}
private:
  std::string	_login;

public:
  const int&	getId(void){return (_id);}
  void	setId(const int& id){_id = id;}
private:
  int	_id;

public:
  const int&	getCredit(void){return (_credit);}
  void	setCredit(const int& credit){_credit = credit;}
private:
  int	_credit;

public:
  void	clearBufRead(void);
  void	clearBufWrite(void);
};

#endif // !__CLIENT_H__
