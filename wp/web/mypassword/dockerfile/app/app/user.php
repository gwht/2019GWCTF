<?php

include('db.php');

class User{

	private $users;
	private $psw;

	public function __construct($users,$psw){
		$this->users = $users;
		$this->psw = $psw;
	}

	public function check(){
		if(!preg_match('/^[A-Za-z0-9\-\_]+$/',$this->users)){
			echo "<script>alert('用户名不合法');</script>";
			return false;
		}else if(!preg_match('/^[A-Za-z0-9\-\_]+$/',$this->psw)){
			echo "<script>alert('密码不合法');</script>";
			return false;
		}
		return true;
	}

	public function login(){
		$DB = new Db();
		$ret = $DB->select('psw','gwht_users',"user = '".$this->users."'");
		if($ret){
			$data = $ret->fetch_row();
			if($data[0] == md5($this->psw)){
				return true;
			}
		}
		echo "<script>alert('密码不正确');</script>";
		return false;
	}

	public function exist(){
		$DB = new Db();
		$ret = $DB->select('psw','gwht_users',"user = '".$this->users."'");
		if($ret){
			$data = $ret->fetch_row();
			if($data){
				echo "<script>alert('用户已存在');</script>";
				return false;
			}
		}
		return true;
	}

	public function register(){
		$DB = new Db();
		$ret = $DB->insert('`user`,`psw`','gwht_users',"'".$this->users."','".md5($this->psw)."'");
		if($ret){
			return true;
		}
		echo "<script>alert('注册失败');</script>";
		return false;
	}

}