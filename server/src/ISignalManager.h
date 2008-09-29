//
// ISignalManager.h for server in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 15:56:48 2008 caner candan
// Last update Mon Sep 29 01:03:02 2008 caner candan
//

#ifndef __ISIGNALMANAGER_H__
# define __ISIGNALMANAGER_H__

class	ISignalManager
{
public:
  typedef void	(ISignalManager::*callback)(void);

  virtual ~ISignalManager(){}
};

#endif // !__ISIGNALMANAGER_H__
