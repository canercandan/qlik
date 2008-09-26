//
// Singleton.hpp for Singleton in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 00:22:13 2008 caner candan
// Last update Sun Aug 17 00:58:57 2008 caner candan
//

#ifndef __SINGLETON_HPP__
# define __SINGLETON_HPP__

# include <cstdlib>

template <typename T>
class	Singleton
{
public:
  static T*	getInstance()
  {
    if (!_singleton)
      _singleton = new T;
    return (static_cast<T*>(_singleton));
  }

  static void	kill()
  {
    if (_singleton)
      {
	delete _singleton;
	_singleton = NULL;
      }
  }
protected:
  Singleton(){}
  ~Singleton(){}
private:
  static T*	_singleton;
};

template <typename T>
T*	Singleton<T>::_singleton = NULL;

#endif // !__SINGLETON_HPP__
