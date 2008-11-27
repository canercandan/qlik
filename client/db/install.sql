--install.sql --- 
--
--Filename: install.sql
--Description: 
--Author: Caner Candan
--Maintainer: 
--Created: Thu Nov 27 01:11:40 2008 (+0200)
--Version: 
--Last-Updated: Thu Nov 27 19:17:27 2008 (+0200)
--          By: Caner Candan
--    Update #: 7
--URL: 
--Keywords: 
--Compatibility: 
--
--

--Commentary: 
--
--
--
--

--Change log:
--
--
--
--
--This program is free software; you can redistribute it and/or
--modify it under the terms of the GNU General Public License as
--published by the Free Software Foundation; either version 3, or
--(at your option) any later version.
--
--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
--General Public License for more details.
--
--You should have received a copy of the GNU General Public License
--along with this program; see the file COPYING.  If not, write to
--the Free Software Foundation, Inc., 51 Franklin Street, Fifth
--Floor, Boston, MA 02110-1301, USA.

--
--

--Code:

------------------------------------------------------------------
-- create tables
------------------------------------------------------------------

create table options
(
	key text unique,
	value text
);

create table users
(
	username text unique,
	password text
);

create table history
(
	id integer primary key autoincrement,
	username text,
	type integer,
	describe text,
	price integer,
	date integer
);

create table messages
(
	id integer primary key autoincrement,
	username text,
	contact text,
	body text,
	date integer
);

create table contacts
(
	id integer primary key autoincrement,
	username text,
	contact text,
	alias text
);

------------------------------------------------------------------
-- insert values
------------------------------------------------------------------

insert into options values("host", "91.121.102.113");
insert into options values("port", "4242");
insert into options values("mask", "0");

--
--install.sql ends here
