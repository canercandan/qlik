create table users
(
	id integer primary key autoincrement,
	username text,
	password text
);

create table history
(
	id integer primary key autoincrement,
	id_user integer,
	type integer,
	describe text,
	price integer,
	date integer
);

create table messages
(
	id integer primary key autoincrement,
	id_user integer,
	ufrom text,
	uto text,
	body text,
	date integer
);
