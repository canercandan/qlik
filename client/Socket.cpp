//
// Socket.cpp for Socket in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 12:27:49 2008 caner candan
// Last update Mon Aug 18 18:43:23 2008 caner candan
//

#include "Socket.h"

Socket::Socket()
  : _socket(new QTcpSocket)
{}

Socket::~Socket()
{
  close();
  delete _socket;
}

QTcpSocket*	Socket::socket()
{
  return (this->_socket);
}

void	Socket::connect(const QString& host,
			const int& port)
{
  this->close();
  this->socket()->connectToHost(host, port);
}

void	Socket::close()
{
  if (this->_socket->state() == QAbstractSocket::ConnectedState)
    this->socket()->close();
}
