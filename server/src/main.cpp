// main.cpp --- 
// 
// Filename: main.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:18:32 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 15:31:12 2008 (+0200)
//           By: Caner Candan
//     Update #: 81
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 27-Nov-2008    Caner Candan  
//    Last-Updated: Thu Nov 27 15:28:50 2008 (+0200) #79 (Caner Candan)
//    add an usage, get options
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.

// 
// 

// Code:

#include <iostream>
#include <iomanip>
#include "Server.h"
#include "Config.h"

static void	usage(std::string filename)
{
  std::cout << "Usage: " << filename
	    << " [option(s)]" << std::endl
	    << "The options are:" << std::endl
	    << std::left << std::setw(25) << "  -f [file]"
	    << "Select a file of config" << std::endl
	    << std::endl
	    << "Report bugs to candanc42@gmail.com." << std::endl;
}

static bool	getOption(int ac, char** av)
{
  if (ac < 2)
    {
      usage(av[0]);
      return (false);
    }

  bool	flagF = false;
  int	ch;

  while ((ch = getopt(ac, av, "f:h")) != -1)
    {
      if (ch == 'f')
	{
	  Config*	config = Config::getInstance();

	  config->fillFromFile(std::string(optarg));
	  flagF = true;
	}
      else
	{
	  usage(av[0]);
	  return (false);
	}
    }
  ac -= optind;
  av += optind;

  return (flagF);
}

int		main(int ac, char** av)
{
  if (!getOption(ac, av))
    {
      Config::kill();
      return (-1);
    }

  Config*	config = Config::getInstance();

  if (config->isDaemon())
    {
      pid_t		pid;

      if ((pid = fork()))
	{
	  std::cout << "Server started..." << std::endl
		    << "Detached to pid [" << pid << "]." << std::endl;
	  return (0);
	}
    }

  Server	s;

  s.start();

  return (0);
}

// 
// main.cpp ends here
