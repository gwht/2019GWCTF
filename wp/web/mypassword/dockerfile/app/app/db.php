<?php

class Db{

	private $servername = "localhost";
	private $username = "gwhtK0T0R1";
	private $password = "7a6e3af0b";
	private $dbname = "gwhtctf";
    private $conn;

    public function __construct(){
    	$this->conn = new mysqli($this->servername, $this->username, $this->password, $this->dbname);
    }

    public function __destruct()
    {
        $this->conn->close();
    }

    public function select($column,$table,$where) {
        $sql = 'select '.$column.' from '.$table.' where '.$where.';';
        $ret = $this->conn->query($sql);
        return $ret;
    }

    public function insert($column,$table,$value) {
        $sql = 'insert into '.$table.'('.$column.') values ('.$value.');';
        $ret = $this->conn->query($sql);
        return $ret;
    }

    public function delete($table,$where){
        $sql = 'delete from '.$table.' where '.$where.';';
        $ret = $this->conn->query($sql);
        return $ret;
    }

}