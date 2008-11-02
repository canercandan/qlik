//
// Stream.h for server in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Oct 12 18:39:48 2008 caner candan
// Last update Sun Oct 12 19:07:25 2008 caner candan
//

#ifndef __STREAM_H__
# define __STREAM_H__

# include <string>

class	Stream
{
public:
  Stream();
  ~Stream();
  Stream(const Stream&);
  Stream&	operator=(const Stream&);
public:
  const std::string&	getLogin(void){return (_login);}
  void	setLogin(const std::string& login){_login = login;}
private:
  std::string	_login;
public:
  const std::string&	getName(void){return (_name);}
  void	setName(const std::string& name){_name = name;}
private:
  std::string	_name;
public:
  const int&	getSlots(void){return (_slots);}
  void	setSlots(const int& slots){_slots = slots;}
private:
  int	_slots;
public:
  const int&	getBits(void){return (_bits);}
  void	setBits(const int& bits){_bits = bits;}
private:
  int	_bits;
public:
  const std::string&	getTitle(void){return (_title);}
  void	setTitle(const std::string& title){_title = title;}
private:
  std::string	_title;
public:
  const int&	getPort(void){return (_port);}
  void	setPort(const int& port){_port = port;}
private:
  int	_port;
};

#endif // !__STREAM_H__
