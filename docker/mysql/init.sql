use best_server;

CREATE TABLE clients(
  login varchar(255) NOT NULL,
  first_name varchar(255) NOT NULL,
  last_name varchar(255) NOT NULL,
  age int NOT NULL
);


INSERT INTO clients (login, first_name, last_name, age) VALUES
('guhab', 'Maksim', 'Kukushkin', 22),
('super puper', 'Kolib', 'Irov', 45),
('splf', 'Misterio', 'Kirrilov', 65);