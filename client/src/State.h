// State.h --- 
// 
// Filename: State.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:05:14 2008 (+0200)
// Version: 
// Last-Updated: Wed Dec  3 01:48:05 2008 (+0200)
//           By: Caner Candan
//     Update #: 16
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

#ifndef __STATE_H__
# define __STATE_H__

# include "Singleton.hpp"

class	State : public Singleton<State>
{
  friend class	Singleton<State>;
public:
  enum	List {WAIT, DONE};

private:
  State();

public:
  const List&	getWebList(void){return (_weblist);}
  void	setWebList(const List& weblist){_weblist = weblist;}
private:
  List	_weblist;

public:
  const List&	getStreamList(void){return (_streamlist);}
  void	setStreamList(const List& streamlist){_streamlist = streamlist;}
private:
  List	_streamlist;

public:
  const List&	getClientsList(void){return (_clientslist);}
  void	setClientsList(const List& clientslist){_clientslist = clientslist;}
private:
  List	_clientslist;

public:
  const List&	getAccountsList(void){return (_accountslist);}
  void	setAccountsList(const List& accountslist){_accountslist = accountslist;}
private:
  List	_accountslist;

public:
  const List&	getCreditList(void){return (_creditlist);}
  void	setCreditList(const List& creditlist){_creditlist = creditlist;}
private:
  List	_creditlist;

public:
  const List&	getOfferWebList(void){return (_offerweblist);}
  void	setOfferWebList(const List& offerweblist){_offerweblist = offerweblist;}
private:
  List	_offerweblist;

public:
  const List&	getOfferStreamList(void){return (_offerstreamlist);}
  void	setOfferStreamList(const List& offerstreamlist){_offerstreamlist = offerstreamlist;}
private:
  List	_offerstreamlist;

public:
  const List&	getNewsList(void){return (_newslist);}
  void	setNewsList(const List& newslist){_newslist = newslist;}
private:
  List	_newslist;
};

#endif // !__STATE_H__

// 
// State.h ends here
