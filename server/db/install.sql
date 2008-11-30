--install.sql --- 
--
--Filename: install.sql
--Description: 
--Author: Caner Candan
--Maintainer: 
--Created: Thu Nov 27 01:42:06 2008 (+0200)
--Version: 
--Last-Updated: Sun Nov 30 03:56:14 2008 (+0200)
--          By: Caner Candan
--    Update #: 12
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

create table	users
(
	id		integer	primary key	autoincrement	,
	username	text					,
	password	text					,
	credit		integer					,
	right		integer
);

create table	credits
(
	id		integer primary key	autoincrement	,
	id_user		integer					,
	credit		integer					,
	date		integer
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

------------------------------------------------------------------
-- insert values
------------------------------------------------------------------

insert into users values(1,	"admin",	"totitoti",	0,	57);
insert into users values(2,	"candan_c",	"totitoti",	0,	57);
insert into users values(3,	"starke_g",	"totitoti",	0,	57);
insert into users values(4,	"finance",	"totitoti",	0,	41);
insert into users values(5,	"demo",		"demo",		100,	15);

insert into offer_web values("Web100",	100,	1,	1);
insert into offer_web values("Web200",	200,	2,	2);
insert into offer_web values("Web300",	300,	3,	3);
insert into offer_web values("Web400",	400,	4,	4);

insert into offer_stream values("Strm05",	5,	24,	1);
insert into offer_stream values("Strm10",	10,	32,	2);
insert into offer_stream values("Strm15",	15,	48,	3);
insert into offer_stream values("Strm20",	20,	64,	4);

--
--install.sql ends here
