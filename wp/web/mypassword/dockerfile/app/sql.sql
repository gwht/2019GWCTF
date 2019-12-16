CREATE database gwhtctf;
use gwhtctf;
create table gwht_users (user varchar(50),psw varchar(50));
create table gwht_feedback (id int PRIMARY KEY AUTO_INCREMENT,user varchar(50),feedback text CHARACTER SET utf8mb4);
CREATE USER 'gwhtK0T0R1'@'localhost' IDENTIFIED BY '7a6e3af0b';
grant all privileges on `gwhtctf`.* to 'gwhtK0T0R1'@'%' identified by '7a6e3af0b';