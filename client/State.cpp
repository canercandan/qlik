//
// State.cpp for State in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 12:27:49 2008 caner candan
// Last update Tue Aug 19 03:24:28 2008 caner candan
//

#include "State.h"

State::State()
{
  reset();
}

void	State::reset()
{
  this->setWebList(WAIT);
  this->setStreamList(WAIT);
}

const State::List&	State::getWebList() const
{
  return (this->_web);
}

void	State::setWebList(const State::List& state)
{
  this->_web = state;
}

const State::List&	State::getStreamList() const
{
  return (this->_stream);
}

void	State::setStreamList(const State::List& state)
{
  this->_stream = state;
}
