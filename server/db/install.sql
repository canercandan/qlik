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
