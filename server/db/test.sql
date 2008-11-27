--test.sql --- 
--
--Filename: test.sql
--Description: 
--Author: Caner Candan
--Maintainer: 
--Created: Thu Nov 27 01:42:11 2008 (+0200)
--Version: 
--Last-Updated: Thu Nov 27 01:43:46 2008 (+0200)
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

insert into users values(1,	"Caner",	"caca",	100,	57);
insert into users values(2,	"Nulufer",	"caca",	2,	15);
insert into users values(3,	"Geraldine",	"caca",	0,	15);

insert into web values(1,	"COOL_WEB",	100,	2,	"coco.com",	-1,	-1);

insert into stream values(2,	"Streamminnngg",	12,	24,	"title",	9000,	0,	-1,	-1);

insert into offer_web values("Web100",	100,	1,	1);
insert into offer_web values("Web200",	200,	2,	2);
insert into offer_web values("Web300",	300,	3,	3);
insert into offer_web values("Web400",	400,	4,	4);

insert into offer_stream values("Strm05",	5,	24,	1);
insert into offer_stream values("Strm10",	10,	32,	2);
insert into offer_stream values("Strm15",	15,	48,	3);
insert into offer_stream values("Strm20",	20,	64,	4);

insert into news values(null,	1,	"ouverture", "welcome to new software of ekzay",	-1);

--
--test.sql ends here
