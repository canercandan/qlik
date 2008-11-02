//
// Signal.h for server in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 15:56:41 2008 caner candan
// Last update Mon Oct 27 15:24:25 2008 caner candan
//

#ifndef __SIGNAL_H__
# define __SIGNAL_H__

# include <list>
# include <map>
# include "Singleton.hpp"
# include "ISignalManager.h"

class	Signal : public Singleton<Signal>
{
  friend class	Singleton<Signal>;
public:
  enum	Type {INT, TERM};
  enum	Priority {HIGH, NORMAL, LOW};

  typedef std::pair<ISignalManager*, ISignalManager::callback>	pairCallback;
  typedef std::list<pairCallback>				listCallback;
  typedef std::map<Priority, listCallback>			mapPriority;
  typedef std::map<Type, mapPriority>				mapSignal;

  void	addCallback(const Type&, const Priority&,
		    ISignalManager*, ISignalManager::callback);
private:
  Signal();
  ~Signal();

  static void	_sigInt(int);
  static void	_sigTerm(int);

  void	_signalLoop(const Type&);
  void	_signalLoopPriority(const Type&, const Priority&);
private:
  mapSignal	_signals;
};

#endif // !__SIGNAL_H__
