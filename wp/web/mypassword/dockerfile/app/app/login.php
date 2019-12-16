<?php
include("header.php");
include("user.php");

if(isset($_SESSION['user'])){
	echo "<script>self.location='index.php';</script>";
	exit();
}

if(isset($_POST['username'])&&isset($_POST['password'])){
	if(!$_POST['username']){
		echo "<script>alert('用户名为空');self.location='login.php';</script>";
		exit();
	}else if(!$_POST['password']){
		echo "<script>alert('密码为空');self.location='login.php';</script>";
		exit();
	}
	$users = $_POST['username'];
	$psw = $_POST['password'];
	$remember = isset($_POST['remember'])?$_POST['remember']:'';
	if("admin" == $users){
		$flag = file_get_contents('/flag');
		if($flag == $psw){
			$_SESSION['user'] = 'admin';
			$_SESSION['is_admin'] = 1;
		}
	}else{
		$user = new User($users,$psw);
		if(!$user->check()||!$user->login()){
			echo "<script>self.location='login.php';</script>";
			exit();
		}
		$_SESSION['user'] = $users;
		$_SESSION['is_admin'] = 0;
	}
	if($remember){
		setcookie('user',$users);
		setcookie('psw',$psw);
	}
	echo "<script>self.location='index.php';</script>";
}else{
	?>
					<li class="active"><a href="login.php">Login</a></li>
					<li><a href="register.php">Register</a></li>
				</ul>
			</div>
		</div>
	</nav>
	<div class="container">
	    <div class="row row-centered row-middle">
	        <div class="col-md-4 col-md-offset-4">
	            <div class="panel panel-default">
	                <div class="panel-heading">登录信息</div>
	                <div class="panel-body">
	                    <form action="login.php" method="POST">
	                        <div class="form-group">
	                            <input type="text" class="form-control" name="username" placeholder="用户名">
	                        </div>
	                        <div class="form-group">
	                            <input type="password" class="form-control" name="password" placeholder="密码">
	                        </div>
	                        <div class="checkbox">
	                            <label>
	                                <input type="checkbox" name="remember">记住密码
	                            </label>
	                        </div>
	                        <button type="submit" class="btn btn-info btn-block btn-lg">登录</button>
	                    </form>
	                </div>
	            </div>
	        </div>
	    </div>
	</div>
	<script src="./js/login.js"></script>
</body>
</html>
<?php
}
?>
	
