//
// State.cpp for State in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 00:28:11 2008 caner candan
// Last update Sun Aug 17 00:39:46 2008 caner candan
//

#include "State.h"

State::State()
  : _state(START)
{}

State::~State()
{}

void	State::setState(const State::Step& state)
{
  this->_state = state;
}

const State::Step&	State::getState() const
{
  return (this->_state);
}
