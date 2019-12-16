<?php
include("header.php");
include("db.php");

if(!isset($_SESSION['user'])){
	echo "<script>self.location='login.php';</script>";
	exit();
}
?>
					<li><a href="index.php">Index</a></li>
					<li><a href="feedback.php">Feedback</a></li>
					<li class="active"><a href="list.php">List</a></li>
					<li><a href="logout.php">Logout</a></li>
				</ul>
			</div>
		</div>
	</nav>
	<div class="container container-middle">
		<table class="table" style="width:200px;">
			<thead>
				<tr>
					<th class="col-md-3">#</th>
					<th class="col-md-1"></th>
				</tr>
			</thead>
<?php
$DB = new Db();
$user = $_SESSION['user'];
if("admin" == $user){
	$ret = $DB->select('id','gwht_feedback',"1 order by id desc limit 10");
}else{
	$ret = $DB->select('id','gwht_feedback',"user = '".$user."' order by id desc limit 10");	
}
if($ret){		
?>
			<tbody>
<?php
	$data = $ret->fetch_row();
	$i = 1;
	while($data){
?>
			<tr>
				<td class="col-md-3"><a href=<?php echo "content.php?id=".(string)$data[0];?>><?php echo $i;?></a></td>
				<td class="col-md-1"><a href=<?php echo "delete.php?id=".(string)$data[0];?>>删除</a></td>
			</tr>
<?php
		$data = $ret->fetch_row();
		$i++;
	}
?>
			</tbody>
		
<?php
}
?>
		</table>
	</div>
</body>
</html>
