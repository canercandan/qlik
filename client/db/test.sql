--test.sql --- 
--
--Filename: test.sql
--Description: 
--Author: Caner Candan
--Maintainer: 
--Created: Thu Nov 27 01:12:56 2008 (+0200)
--Version: 
--Last-Updated: Thu Nov 27 01:13:11 2008 (+0200)
--          By: Caner Candan
--    Update #: 2
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

insert into options values("host", "localhost");
insert into options values("port", "4242");
insert into options values("mask", "0");

insert into users values("Caner", "caca");

insert into history values(null, "Caner", 0, "create web service", 10, -1);

insert into messages values(null, "Caner", "Lulu", "salut", -1);

insert into contacts values(null, "Caner", "Lulu", "nulufer");
insert into contacts values(null, "Caner", "finance", "finance contact");

--
--test.sql ends here
