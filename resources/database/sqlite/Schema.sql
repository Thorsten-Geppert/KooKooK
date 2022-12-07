CREATE TABLE users (
	username TEXT,
	password TEXT,
	active INTEGER DEFAULT false,
	PRIMARY KEY (username)
);

INSERT INTO users VALUES ('user1', 'password1', true);
INSERT INTO users VALUES ('user2', 'password2', true);
INSERT INTO users VALUES ('user3', 'password3', false);
INSERT INTO users VALUES ('user4', 'password4', false);
INSERT INTO users VALUES ('user5', 'password5', true);
