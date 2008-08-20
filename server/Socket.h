//
// Socket.h for Socket in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 13:20:30 2008 caner candan
// Last update Sat Aug 16 22:14:00 2008 caner candan
//

#ifndef __SOCKET_H__
# define __SOCKET_H__

# include <string>

class	Socket
{
public:
  Socket();
  Socket(const Socket&);
  ~Socket();
  Socket&	operator=(const Socket&);

  void		closeSocket(void);
  void		send(const std::string& s);
  std::string	recv();
  std::string	sendRecv(const std::string& s);
  bool		isConnected(void) const;
  bool		isGoodRecv(void) const;

  int		getSocket(void) const;
  bool		getStatus(void) const;

  void		setStatus(bool status);

  std::string	head(void);
protected:
  int	_socket;
  bool	_status;
};

#endif // !__SOCKET_H__
