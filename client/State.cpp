//
// State.cpp for State in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 12:27:49 2008 caner candan
// Last update Sun Aug 17 13:55:27 2008 caner candan
//

#include "State.h"

State::State()
  : _web(WAIT), _stream(WAIT)
{}

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
