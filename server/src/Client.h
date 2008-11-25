//
// Client.h for Client in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 08:50:46 2008 caner candan
// Last update Sat Nov 15 02:22:07 2008 caner candan
//

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <string>
# include "Socket.h"

class	Client
{
public:
  enum	Type {SERVER, CLIENT};
public:
  Client(Socket* socket = NULL, Type type = SERVER);
  Client(const Client&);
  ~Client();
  Client&	operator=(const Client&);

public:
  Socket*	socket(void){return (_socket);}
private:
  Socket*	_socket;

public:
  bool	isConnected();

public:
  const std::string&	getBufRead(void){return (_bufread);}
  void	appendBufRead(const std::string& bufread){_bufread += bufread;}
  void	appendBufRead(const int& bufread);
  void	clearBufRead(void){_bufread.clear();}
private:
  std::string	_bufread;

public:
  const std::string&	getBufWrite(void){return (_bufwrite);}
  void	appendBufWrite(const std::string& bufwrite){_bufwrite += bufwrite;}
  void	appendBufWrite(const int& bufwrite);
  void	clearBufWrite(void){_bufwrite.clear();}
private:
  std::string	_bufwrite;

public:
  const Type&	getType(void){return (_type);}
  void	setType(const Type& type){_type = type;}
private:
  Type	_type;

public:
  const int&	getRight(void){return (_right);}
  void	setRight(const int& right){_right = right;}
private:
  int	_right;

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
};

#endif // !__CLIENT_H__
