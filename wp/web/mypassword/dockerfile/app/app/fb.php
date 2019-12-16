<?php

include('db.php');

class Fb{

	private $user;
	private $feedback;

	public function __construct($user,$feedback){
		$this->user = $user;
		$this->feedback = $feedback;
	}

	public function check(){
		if(is_array($this->feedback)){
			echo "<script>alert('反馈不合法');</script>";
			return false;
		}
		$blacklist = ['_','\'','&','\\','#','%','input','script','iframe','host','onload','onerror','srcdoc','location','svg','form','img','src','getElement','document','cookie'];
		foreach ($blacklist as $val) {
	        while(true){
	            if(stripos($this->feedback,$val) !== false){
	                $this->feedback = str_ireplace($val,"",$this->feedback);
	            }else{
	                break;
	            }
	        }
	    }
		return true;
	}

	public function submit(){
		$DB = new Db();
		$ret = $DB->insert('`user`,`feedback`','gwht_feedback',"'".$this->user."','".$this->feedback."'");
		if($ret){
			return true;
		}
		echo "<script>alert('提交失败');</script>";
		return false;
	}

}