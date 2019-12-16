<?php
include("header.php");
include('fb.php');

if(!isset($_SESSION['user'])){
	echo "<script>self.location='login.php';</script>";
	exit();
}

if(isset($_POST['feedback'])){
	if(!$_POST['feedback']){
		echo "<script>alert('反馈内容为空');self.location='feedback.php';</script>";
		exit();
	}
	$user = $_SESSION['user'];
	$feedback = $_POST['feedback'];
	$fb = new Fb($user,$feedback);
	if(!$fb->check()||!$fb->submit()){
		echo "<script>self.location='feedback.php';</script>";
		exit();
	}else{
		echo "<script>alert('提交成功');self.location='feedback.php';</script>";
	}
}else{
?>
					<li><a href="index.php">Index</a></li>
					<li class="active"><a href="feedback.php">Feedback</a></li>
					<li><a href="list.php">List</a></li>
					<li><a href="logout.php">Logout</a></li>
					
				</ul>
			</div>
		</div>
	</nav>
	<div class="container container-middle">
		<div class="starter-template">
			<p class="lead">网站还在开发中，有什么建议请多多提出</p>
			<!-- 
			if(is_array($feedback)){
				echo "<script>alert('反馈不合法');</script>";
				return false;
			}
			$blacklist = ['_','\'','&','\\','#','%','input','script','iframe','host','onload','onerror','srcdoc','location','svg','form','img','src','getElement','document','cookie'];
			foreach ($blacklist as $val) {
		        while(true){
		            if(stripos($feedback,$val) !== false){
		                $feedback = str_ireplace($val,"",$feedback);
		            }else{
		                break;
		            }
		        }
		    }
		    -->
		</div>
		<form role="form" action="feedback.php" method="POST">
			<div class="form-group">
				<label for="name">反馈</label>
				<textarea class="form-control" rows="15" name="feedback"></textarea>
				<br>
				<button type="submit" class="btn btn-info btn-block btn-lg">提交</button>
			</div>
		</form>
	</div>
</body>
</html>
<?php
}
?>
