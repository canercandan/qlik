//
// Socket.h for Socket in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 13:20:30 2008 caner candan
// Last update Thu Nov 13 22:39:50 2008 caner candan
//

#ifndef __SOCKET_H__
# define __SOCKET_H__

# include <string>

class	Socket
{
public:
  Socket();
  ~Socket();

  void	closeSocket(void);

  void		send(std::string s);
  std::string	recv();
  std::string	sendRecv(std::string s);

  bool	isConnected(void) const;
  bool	isGoodRecv(void) const;
public:
  const int&	socket(void){return (_socket);}
protected:
  int	_socket;
public:
  const bool&	getStatus(void){return (_status);}
  void	setStatus(const bool& status){_status = status;}
private:
  bool	_status;
};

#endif // !__SOCKET_H__
