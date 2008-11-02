//
// Singleton.hpp for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sat Oct 25 21:08:36 2008 caner candan
// Last update Sat Oct 25 21:08:36 2008 caner candan
//

#ifndef __SINGLETON_H__
# define __SINGLETON_H__

# include <cstdlib>

template <typename T>
class	Singleton
{
protected:
  Singleton(){}
  ~Singleton(){}
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

  static bool	exist()
  {return (_singleton != NULL);}
private:
  static T*	_singleton;
};

template <typename T>
T*	Singleton<T>::_singleton = NULL;

#endif // !__SINGLETON_H__
