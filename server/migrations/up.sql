/* Up migration file */

CREATE TABLE users
(
  id SERIAL PRIMARY KEY,
  login VARCHAR(100) NOT NULL UNIQUE,
  password VARCHAR(50) NOT NULL,
  token UUID,
  token_date TIMESTAMP
);

CREATE TABLE web_links
(
  id SERIAL PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  description VARCHAR(200),
  link_date TIMESTAMP NOT NULL,
  link_uuid UUID NOT NULL
);

CREATE TABLE snapshots
(
  id SERIAL PRIMARY KEY,
  snapshot_uuid UUID NOT NULL UNIQUE,
  dir_name VARCHAR(100) NOT NULL,
  link_id INT REFERENCES web_links,
  snapshot_date TIMESTAMP NOT NULL
);

CREATE TABLE comments
(
  id SERIAL PRIMARY KEY,
  content VARCHAR(100) NOT NULL,
  link_id INT REFERENCES web_links
);

CREATE TABLE rooms
(
  id SERIAL PRIMARY KEY,
  room_date TIMESTAMP NOT NULL,
  private BOOLEAN NOT NULL,
  user_id INT REFERENCES users
);

CREATE TABLE room_links
(
  id SERIAL PRIMARY KEY,
  room_id INT REFERENCES rooms,
  link_id INT REFERENCES web_links
);

CREATE TABLE room_users
(
  id SERIAL PRIMARY KEY,
  room_id INT REFERENCES rooms,
  user_id INT REFERENCES users
);
