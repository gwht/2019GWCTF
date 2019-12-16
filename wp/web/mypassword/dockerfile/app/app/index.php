<?php
include("header.php");

if(!isset($_SESSION['user'])){
	echo "<script>self.location='login.php';</script>";
	exit();
}
?>
					<li class="active"><a href="index.php">Index</a></li>
					<li><a href="feedback.php">Feedback</a></li>
					<li><a href="list.php">List</a></li>
					<li><a href="logout.php">Logout</a></li>
				</ul>
			</div>
		</div>
	</nav>
	<div class="container container-middle">
		<div class="starter-template">
			<p class="lead">欢迎！<?php echo $_SESSION['user']?></p>
			<p class="lead">我把密码写进了源码里，注入是不可能注入的了，这辈子都别想注入出来</p>
		</div>
	</div>
</body>
</html>

