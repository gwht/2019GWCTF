# 枯燥的抽奖
进到题目看到的是一个猜数字题目，然后从前端跟到check.php可以看到后台代码

```php
<?php
#这不是抽奖程序的源代码！不许看！
header("Content-Type: text/html;charset=utf-8");
session_start();
if(!isset($_SESSION['seed'])){
$_SESSION['seed']=rand(0,999999999);
}

mt_srand($_SESSION['seed']);
$str_long1 = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
$str='';
$len1=20;
for ( $i = 0; $i < $len1; $i++ ){
    $str.=substr($str_long1, mt_rand(0, strlen($str_long1) - 1), 1);       
}
$str_show = substr($str, 0, 10);
echo "<p id='p1'>".$str_show."</p>";


if(isset($_POST['num'])){
	if($_POST['num']===$str){x
		echo "<p id=flag>抽奖，就是那么枯燥且无味，给你flag{xxxxxxxxx}</p>";
	}
	else{
		echo "<p id=flag>没抽中哦，再试试吧</p>";
	}
}
show_source("check.php");
```

想到是关于php伪随机数的破解，问下度娘可以找到[解法](https://xz.aliyun.com/t/3656#toc-3)

具体解法是先用脚本将伪随机数转换成php_mt_seed可以识别的数据（参考解法）

```python
str1='abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'
str2='yTPhFFRT7B'
str3 = str1[::-1]
length = len(str2)
res=''
for i in range(len(str2)):  
    for j in range(len(str1)):
        if str2[i] == str1[j]:
            res+=str(j)+' '+str(j)+' '+'0'+' '+str(len(str1)-1)+' '
            break
print(res)

```

然后将生成的数据放到php_mt_seed中爆破，可以爆破出伪随机数和php版本.
然后改写源码，生成完整字符串（如爆破到的seed是111794312）

```php
<?php
mt_srand(111794312);
$str_long1 = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
$str='';
$len1=20;
for ( $i = 0; $i < $len1; $i++ ){
    $str.=substr($str_long1, mt_rand(0, strlen($str_long1) - 1), 1);       
}
echo "<p id='p1'>".$str."</p>";
```

提交得flag。
