//
// State.h for State in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 00:22:29 2008 caner candan
// Last update Mon Oct 27 18:22:59 2008 caner candan
//

#ifndef __STATE_H__
# define __STATE_H__

# include "Singleton.hpp"

class	State : public Singleton<State>
{
  friend class	Singleton<State>;
public:
  enum	LoopState {LOOP_START, LOOP_STOP, LOOP_ERROR};
  enum	ProcessState {PROCESS_BREAK, PROCESS_PLAY};
public:
  const LoopState&	getLoopState(void){return (_loopstate);}
  void	setLoopState(const LoopState& loopstate){_loopstate = loopstate;}
private:
  LoopState	_loopstate;
public:
  const ProcessState&	getProcessState(void){return (_processstate);}
  void	setProcessState(const ProcessState& processstate){_processstate = processstate;}
private:
  ProcessState	_processstate;
private:
  State();
};

#endif // !__STATE_H__
