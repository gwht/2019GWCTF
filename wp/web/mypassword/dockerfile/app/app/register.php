<?php
include("header.php");
include("user.php");

if(isset($_SESSION['user'])){
	echo "<script>self.location='index.php';</script>";
	exit();
}

if(isset($_POST['username'])&&isset($_POST['password'])){
	if(!$_POST['username']){
		echo "<script>alert('用户名为空');self.location='register.php';</script>";
		exit();
	}else if(!$_POST['password']){
		echo "<script>alert('密码为空');self.location='register.php';</script>";
		exit();
	}
	$users = $_POST['username'];
	$psw = $_POST['password'];
	if("admin" == $users){
		echo "<script>alert('用户已存在');self.location='register.php';</script>";
		exit();
	}else{
		$user = new User($users,$psw);
		if(!$user->check()||!$user->exist()||!$user->register()){
			echo "<script>self.location='register.php';</script>";
			exit();
		}
	}
	echo "<script>alert('注册成功');self.location='login.php';</script>";
}else{
	?>
					<li><a href="login.php">Login</a></li>
					<li class="active"><a href="register.php">Register</a></li>
				</ul>
			</div>
		</div>
	</nav>
	<div class="container">
	    <div class="row row-centered row-middle">
	        <div class="col-md-4 col-md-offset-4">
	            <div class="panel panel-default">
	                <div class="panel-heading">注册信息</div>
	                <div class="panel-body">
	                    <form action="register.php" method="POST">
	                        <div class="form-group">
	                            <input type="text" class="form-control" name="username" placeholder="用户名">
	                        </div>
	                        <div class="form-group">
	                            <input type="password" class="form-control" name="password" placeholder="密码">
	                        </div>
	                        <button type="submit" class="btn btn-info btn-block btn-lg">注册</button>
	                    </form>
	                </div>
	            </div>
	        </div>
	    </div>
	</div>
</body>
</html>
<?php
}
?>
	
