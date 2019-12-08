### 一、pyre

逆向签到题，一个求余，一个异或加密，直接逆即可。

```python
a = ['\x1f', '\x12', '\x1d', '(', '0', '4', '\x01', '\x06', '\x14', '4', ',', '\x1b', 'U', '?', 'o', '6', '*', ':', '\x01', 'D', ';', '%', '\x13']
l = len(a)
print l
a = map(ord,a)
for i in range(l-1,0,-1):
	a[i-1] = a[i-1]^a[i]
code = ''
for i in range(l):
	num = (a[i]-i) % 128
	code += chr(num)
print code
```

