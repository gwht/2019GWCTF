## huyao
这个题目拿到两个图片，用stego弄一下发现两张图片合在一起的时候会显示一些横纹，猜测是盲水印，用个GitHub的脚本跑一下就行了  
```shell
python decode.py --original huyao.png --image stillhuyao.png --result res.png
```
最后结果  
![](./img/1.png)
