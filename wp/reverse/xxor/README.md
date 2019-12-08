### 一、xxor

这题一开始出了点小bug，密文的check工作不严谨，修补了一段时间，在此和师傅们道个歉，下面看下这题：

1、tea算法魔改，动态调试可以找出标志数0x458BCD42和key[2,2,3,4]

2、check部分可以通过解方程得到密文：[0xdf48ef7e,0x20caacf4,0xe0f30fd5,0x5c50d8d6,0x9e1bde2d,0x84f30420]

3、每2个2个进行加密，得到6组密文，写脚本反解即可。

4、将输入转成16进制，并拼接转成字符即可得到flag

```c
//gcc -o exp exp.c 
#include <stdio.h>  
#include <stdint.h>  
uint32_t v[2]={0,0},k[4]={2,2,3,4}; 
void decrypt (uint32_t* v, uint32_t* k) {  
    uint32_t v0=v[0], v1=v[1], sum=0x62F35080, i;  /* set up */  
    uint32_t delta=0x458BCD42;                   /* a key schedule constant */  
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */  
    for (i=0; i<64; i++) {                         /* basic cycle start */  
        v1 -= ((((v0<<6) + k2) ^ (v0 + sum + 20) ^ ((v0>>9) + k3))^0x10);  
        v0 -= ((((v1<<6) + k0) ^ (v1 + sum + 11) ^ ((v1>>9) + k1))^0x20);  
        sum -= delta;  
    }                                              /* end cycle */  
    v[0]=v0; v[1]=v1;  
} 

int main()  
{   
    uint32_t v10[10]={0xdf48ef7e,0x20caacf4,0xe0f30fd5,0x5c50d8d6,0x9e1bde2d,0x84f30420};   
    for(int i=0;i<5;i=i+2 )
    {
    v[0] = v10[i];
    v[1] = v10[i+1];
    decrypt(v, k);  
    printf("解密后的数据：%x %x\n",v[0],v[1]);
    }
}
//[0x666c61,0x677b72,0x655f69,0x735f67,0x726561,0x74217d]
//flag{re_is_great!}
```

