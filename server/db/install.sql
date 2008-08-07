create table users
(
	id integer primary key autoincrement,
	username text,
	password text
);

create table credit
(
	id_user integer primary key,
	value integer
);

create table history
(
	id integer primary key autoincrement,
	id_user integer,
	type integer,
	date integer
);

create table services_web
(
	id integer primary key autoincrement,
	id_user integer,
	name text,
	space integer,
	nb_db integer,
	domain text,
	created integer,
	expire integer
);

create table services_stream
(
	id integer primary key autoincrement,
	id_user integer,
	name text,
	slots integer,
	bits integer,
	title text,
	created integer,
	expire integer
);

create table offer_web
(
	id integer primary key autoincrement,
	name text,
	space integer,
	nb_db integer
);

create table offer_stream
(
	id integer primary key autoincrement,
	name text,
	slots integer,
	bits integer
);

create table news
(
	id integer primary key autoincrement,
	id_user integer,
	subject text,
	body text,
	date integer
);
