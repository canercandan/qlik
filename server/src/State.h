//
// State.h for State in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 00:22:29 2008 caner candan
// Last update Sun Aug 17 00:38:42 2008 caner candan
//

#ifndef __STATE_H__
# define __STATE_H__

# include "Singleton.hpp"

class	State : public Singleton<State>
{
  friend class	Singleton<State>;
public:
  enum	Step
    {
      START,
      STOP,
      ERROR
    };

  void		setState(const Step&);
  const Step&	getState() const;
private:
  State();
  ~State();
private:
  Step	_state;
};

#endif // !__STATE_H__
