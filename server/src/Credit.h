//
// Credit.h for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sat Oct 25 17:38:33 2008 caner candan
// Last update Sat Oct 25 21:01:05 2008 caner candan
//

#ifndef __CREDIT_H__
# define __CREDIT_H__

# include "Client.h"

class	Credit
{
public:
  Credit(Client*);
public:
  void	add(const int&);
  void	sub(const int&);

  bool	haveEnoughFor(const int&);
private:
  Client*	_client;
};

#endif // !__CREDIT_H__
