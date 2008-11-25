//
// State.h for State in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 12:23:03 2008 caner candan
// Last update Sun Nov 23 23:59:08 2008 caner candan
//

#ifndef __STATE_H__
# define __STATE_H__

# include "Singleton.hpp"

class	State : public Singleton<State>
{
  friend class	Singleton<State>;
public:
  enum	List {DONE, WAIT};

private:
  State();

public:
  const List&	getWebList(void){return (_weblist);}
  void	setWebList(const List& weblist){_weblist = weblist;}
private:
  List	_weblist;

public:
  const List&	getStreamList(void){return (_streamlist);}
  void	setStreamList(const List& streamlist){_streamlist = streamlist;}
private:
  List	_streamlist;
};

#endif // !__STATE_H__
