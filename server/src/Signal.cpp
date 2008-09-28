//
// Signal.cpp for server in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 15:56:35 2008 caner candan
// Last update Sun Sep 28 15:56:35 2008 caner candan
//

#include <iostream>
#include <csignal>
#include "Signal.h"

Signal::Signal()
{
  ::signal(SIGINT, _sigInt);
  ::signal(SIGTERM, _sigTerm);
}

Signal::~Signal()
{}

void	Signal::addCallback(Signal::Type type,
			    ISignalManager* sm,
			    ISignalManager::callback callback)
{
  this->_signals[type].push_back(pairCallback(sm, callback));
}

void	Signal::_sigInt(int)
{
  Signal::getInstance()->_signalLoop(INT);
}

void	Signal::_sigTerm(int)
{
  Signal::getInstance()->_signalLoop(TERM);
}

void	Signal::_signalLoop(const Type& type)
{
  listCallback&	list = this->_signals[type];

  for (listCallback::iterator
	 it = list.begin(),
	 end = list.end();
       it != end; ++it)
    {
      ISignalManager*		sm = it->first;
      ISignalManager::callback	cb = it->second;

      (sm->*cb)();
    }
  ::exit(-1);
}
