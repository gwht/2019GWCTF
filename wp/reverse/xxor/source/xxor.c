#include <stdio.h>  
#include <stdint.h>  
uint32_t v[2]={0,0},k[4]={2,2,3,4};
//加密函数  
void encrypt (uint32_t* v, uint32_t* k) {  
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */  
    uint32_t delta=0x458BCD42;                     /* a key schedule constant */  
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */  
    for (i=0; i < 64; i++) {                       /* basic cycle start */  
        sum += delta;  
        v0 += ((((v1<<6) + k0) ^ (v1 + sum + 11) ^ ((v1>>9) + k1))^0x20);  
        v1 += ((((v0<<6) + k2) ^ (v0 + sum + 20) ^ ((v0>>9) + k3))^0x10);  
    }                                              /* end cycle */  
    v[0]=v0; v[1]=v1;  
} 
int check(uint32_t* v3)
{

	long long int a = v3[2] - v3[3];
    long long int b = v3[3] + v3[4];
    long long int c = v3[2] - v3[4];
    if(a==0x84a236ff&&b==0xfa6cb703&&c==0x42d731a8)
    {
        if(v3[0]==0xdf48ef7e&&v3[5]==0x84f30420&&v3[1]==0x20caacf4)
        {
            puts("good!");
            return 1;
        }
        else
        {
            puts("Wrong!");
            return 0;
        }
    }
    else
    {
        puts("Wrong!");
        return 0;
    } 	
}
int main()  
{   
    puts("Let us play a game?");
    puts("you have six chances to input");
    puts("Come on!");
    uint32_t v10[10]={0,0,0,0,0,0};
    for(int j=0;j<6;j++)
    {
        printf("%s","input: ",j);
        scanf("%d",&v10[j]);
    }
    uint32_t v20[10]={0,0,0,0,0,0};  
    for(int i=0;i<5;i=i+2 )
    {
    v[0] = v10[i];
    v[1] = v10[i+1];
 
    encrypt(v, k);
    v20[i] = v[0];
    v20[i+1] = v[1];
    }
    if(check(v20)==1)
    {
        puts("Congratulation!\n");
        puts("You seccess half\n");
        puts("Do not forget to change input to hex and combine~\n");
        puts("ByeBye");
    }
    else
    {
        puts("NO NO NO~ ");
        exit(0);
    }
    return 0;  
} 
// gcc -s -o xxor xxor.c
// 0x666c61,0x677b72,0x655f69,0x735f67,0x726561,0x74217d

// 6712417、6781810、6643561、7561063、7497057、7610749

// 0xdf48ef7e、0x20caacf4、0xe0f30fd5、0x5c50d8d6、0x9e1bde2d、0x84f30420