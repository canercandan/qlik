--install.sql --- 
--
--Filename: install.sql
--Description: 
--Author: Caner Candan
--Maintainer: 
--Created: Thu Nov 27 01:42:06 2008 (+0200)
--Version: 
--Last-Updated: Thu Nov 27 01:42:09 2008 (+0200)
--          By: Caner Candan
--    Update #: 1
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

create table	users
(
	id		integer	primary key	autoincrement	,
	username	text					,
	password	text					,
	credit		integer					,
	right		integer
);

create table	web
(
	id_user		integer		,
	name		text		,
	space		integer		,
	nb_db		integer		,
	domain		text		,
	created		integer		,
	expired		integer		,
	primary key	(id_user, name)
);

create table	stream
(
	id_user		integer		,
	name		text		,
	slots		integer		,
	bits		integer		,
	title		text		,
	port		integer		,
	pid		integer		,
	created		integer		,
	expired		integer		,
	primary key	(id_user, name)
);

create table	offer_web
(
	name		text	primary key	,
	space		integer			,
	nb_db		integer			,
	price		integer
);

create table	offer_stream
(
	name		text	primary key	,
	slots		integer			,
	bits		integer			,
	price		integer
);

create table	news
(
	id		integer	primary key	autoincrement	,
	id_user		integer 				,
	subject		text					,
	body		text					,
	date		integer
);

--
--install.sql ends here
