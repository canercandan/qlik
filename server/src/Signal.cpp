//
// Signal.cpp for server in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 15:56:35 2008 caner candan
// Last update Mon Oct 27 15:24:03 2008 caner candan
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

void	Signal::addCallback(const Signal::Type& type, const Signal::Priority& priority,
			    ISignalManager* sm, ISignalManager::callback callback)
{
  _signals[type][priority].push_back(pairCallback(sm, callback));
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
  _signalLoopPriority(type, HIGH);
  _signalLoopPriority(type, NORMAL);
  _signalLoopPriority(type, LOW);

  //::exit(-1);
}

void	Signal::_signalLoopPriority(const Type& type,
				    const Priority& priority)
{
  mapPriority&	map = _signals[type];
  listCallback&	list = map[priority];

  for (listCallback::const_iterator
	 it = list.begin(),
	 end = list.end();
       it != end; ++it)
    {
      ISignalManager*		sm = it->first;
      ISignalManager::callback	cb = it->second;

      (sm->*cb)();
    }
}
