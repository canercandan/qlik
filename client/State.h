//
// State.h for State in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 12:23:03 2008 caner candan
// Last update Tue Aug 19 03:23:50 2008 caner candan
//

#ifndef __STATE_H__
# define __STATE_H__

# include "Singleton.hpp"

class	State : public Singleton<State>
{
  friend class	Singleton<State>;
public:
  enum	List
    {
      DONE,
      WAIT
    };

  void	reset();

  const List&	getWebList() const;
  void		setWebList(const List&);

  const List&	getStreamList() const;
  void		setStreamList(const List&);
private:
  State();
private:
  List	_web;
  List	_stream;
};

#endif // !__STATE_H__
