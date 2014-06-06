DROP TABLE IF EXISTS users;

CREATE TABLE users (
                id INT(10) AUTO_INCREMENT NOT NULL,
                username VARCHAR(15) NOT NULL UNIQUE,
                password VARCHAR(255) NOT NULL,
                PRIMARY KEY (id)
)Engine=InnoDB;