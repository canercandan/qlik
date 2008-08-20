//
// Singleton.hpp for Singleton in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 11:43:18 2008 caner candan
// Last update Sun Aug 17 14:34:01 2008 caner candan
//

#ifndef __SINGLETON_HPP__
# define __SINGLETON_HPP__

# include <cstdlib>
# include <QWidget>

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

  static T*	getInstance(QWidget* parent)
  {
    if (!_singleton)
      _singleton = new T(parent);
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
  {
    return (_singleton);
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
