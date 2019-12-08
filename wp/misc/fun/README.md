## fun
剪刀石头布，撒谎是有规律的，找到规律之后写脚本跑32遍就出flag了
exp:

```python
from pwn import *
context.log_level = 'debug'
# p = process('./misc')
p = remote("183.129.189.60","10035")
sd = lambda s:p.send(s)
sl = lambda s:p.sendline(s)
rc = lambda s:p.recv(s)
ru = lambda s:p.recvuntil(s)
sda = lambda a,s:p.sendafter(a,s)
sla = lambda a,s:p.sendlineafter(a,s)

i = 0
win = "psr"
for _ in range(32):
	ru("take ")
	s = rc(1)
	if s == 'p':
		pay = win[(1+i)%3]
	elif s == 's':
		pay = win[(2+i)%3]
	elif s == 'r':
		pay = win[(0+i)%3]
	i = (i+1)%3
	sla("choice\n",pay)
p.interactive()
```