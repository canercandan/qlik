//
// Socket.h for Socket in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Mon Aug 18 18:45:16 2008 caner candan
//

#ifndef __SOCKET_H__
# define __SOCKET_H__

# include <QtNetwork>
# include "Singleton.hpp"

class	Socket : public Singleton<Socket>
{
  friend class	Singleton<Socket>;
public:
  QTcpSocket*	socket();

  void	connect(const QString& host,
		const int& port);
  void	close();
private:
  Socket();
  ~Socket();
private:
  QTcpSocket*	_socket;
};

#endif // !__SOCKET_H__
