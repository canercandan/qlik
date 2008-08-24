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
