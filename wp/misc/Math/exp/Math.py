#coding=utf8
from pwn import *
context.log_level = 'debug'
context(arch='amd64', os='linux')
local = 1
elf = ELF('./Math')
if local:
    p = process('./Math')
    libc = elf.libc
else:
    p = remote('111.198.29.45',36758)
    libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
sl = lambda s : p.sendline(s)
sd = lambda s : p.send(s)
rc = lambda n : p.recv(n)
ru = lambda s : p.recvuntil(s)
ti = lambda : p.interactive()
v = 0
while v<150:
    ru("problem:")
    a = ru("*")[:-1].strip()
    b = ru("-")[:-1].strip()
    c = ru("+")[:-1].strip()
    d = ru("=")[:-1].strip()
    t = int(a)*int(b)-int(c)+int(d)
    ru("answer:")
    sl(str(t))
    v += 1
sl("cat flag")
p.interactive()