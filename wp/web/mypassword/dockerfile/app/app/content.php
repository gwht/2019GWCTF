<?php
session_start();
include("db.php");

header("Content-Security-Policy: default-src 'self';script-src 'unsafe-inline' 'self'");

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
if("admin" == $user){
	$ret = $DB->select('feedback','gwht_feedback',"id = ".$id);
}else{
	$ret = $DB->select('feedback','gwht_feedback',"id = ".$id." and user = '".$user."'");
}

if(!$ret){
	echo "<script>self.location='list.php';</script>";
	exit();
}
$data = $ret->fetch_row();
echo "<div class=\"container container-middle\">";
echo $data[0];
echo "</div>";
?>