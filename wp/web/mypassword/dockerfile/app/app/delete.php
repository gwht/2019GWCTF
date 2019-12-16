<?php
session_start();
include("db.php");

if(!isset($_SESSION['user'])){
	echo "<script>self.location='login.php';</script>";
	exit();
}

$user = $_SESSION['user'];
if(!isset($_GET['id'])){
	echo "<script>self.location='list.php';</script>";
	exit();
}
$id = $_GET['id'];

if(!preg_match('/^[1-9][0-9]{0,6}$/',$id)){
	echo "<script>alert('id不合法');self.location='list.php';</script>";
	exit();
}

$DB = new Db();
$ret = $DB->delete('gwht_feedback',"id = ".$id." and user = '".$user."'");
if(!$ret){
	echo "<script>alert('删除失败');self.location='list.php';</script>";
	exit();
}else{
	echo "<script>alert('删除成功');self.location='list.php';</script>";
	exit();
}