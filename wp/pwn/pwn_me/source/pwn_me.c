//gcc -o repwn repwn.c
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int gg = 0x20;
int m = 0;
char cd[65];
void vul()
{
  int aa = 0; 
  int ne = 0;
  char memory[600]; 
  char p[600]; 
  memset(memory, 0, 0x258);
  memset(p, 0, 0x258);
  puts("welcome to PWN world!\n");
  puts("please input a magic: ");
  scanf("%d", &aa);
  puts("tell me your dream:\n");
  read(0, p, aa);
  puts("your dream is: ");
  puts(p);
  if ( strlen(p) != 624 )
  {
    puts("What is this?!\n");
    scanf("%d", &ne);
    if(ne<=0)
    {
  	   ne = -ne;
    }
    if(ne>=0)
  {
  	puts("no!");
  	exit(0);
  }
  else
  {
    puts("I think the magic should be 624 hhh");
    memset(p, 0, 0x258);
    read(0, p, 0x270);
    tee(p);
  }
 }
}

void undefind(char s[1024],int l)
{
	for(int i=0;i<l;i++)
	{
		s[i] = i^(s[i]) + 10;
	}
}
void Crypto()
{
	char g[65] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/','='};
	char s[1024];
	puts("please input the secret key~");
	scanf("%s",&s);
	int l = strlen(s);
	undefind(s,l);
	int t = 0;
	char a[3];
	while(t<l){
		char x,y,z,m;
		int temp = 0;
		for(int i=0;i<3;i++){
			if(s[t])
				a[i] = s[t++];
			else{
				a[i] = 0;
				if(i == 1){
					temp = 1;
					break;
				}
				else if(i == 2){
					temp = 2;
					break;
				}
			}				
		}
		if(!temp){
			x = a[0]>>2;
			y = ((a[0]&3)<<4) + (a[1]>>4);
			z = ((a[1]&0xf)<<2) + (a[2]>>6);
			m = (a[2]&0x3f);
		}
		if(!(temp-1)){
			x = a[0]>>2;
			y = ((a[0]&3)<<4) + (a[1]>>4);
			z = 64;
			m = 64;
		}
		if(!(temp-2)){
			x = a[0]>>2;
			y = ((a[0]&3)<<4) + (a[1]>>4);
			z = ((a[1]&0xf)<<2) + (a[2]>>6);
			m = 64;
		}	
		cd[0] = g[x];
		cd[1] = g[y];
		cd[2] = g[z];
		cd[3] = g[m];
	}
}

void tee(char a[600])
{
    if(a[88]==cd[0]&& a[127] == cd[1] && a[137] == cd[2] && a[154] == cd[3])
    {
    	puts("wow cool! hero~");
    }
    else
    {
    	puts("you lost!");
    	exit(0);
    }
}
int check()
{
	puts("there is no thing here,run as fast as you can~");
	if(cd[0] == 'Z'&& cd[1] == 'X'&&cd[2] == 'Z'&&cd[3] == 'l')
		return 1;
	else
		return 0;
}
void tub()
{
	printf("******************\n");
	printf("******************\n");
    printf("Hack world,welcome!\n");
    printf("******************\n");
    printf("******************\n");
    printf("I think you will enjoy it,hhhhh~\n");
    printf("******************\n");
    printf("******************\n");
}
void kk()
{
	m += 1;
}
int xmsl()
{
  char buf[0x50]; // [rsp+10h] [rbp-110h]
  puts("Do you think you are cool?");
  if(CheckIn() == 1 )
  {
    memset(&buf, 0, 0x40);
    puts("say something?: ");
    read(0, &buf, 6);
    printf(&buf);
    kk();
    puts("Maybe I should give you a chance");
    puts("again?");
    read(0,&buf,0x18);
    printf(&buf);
    kk();
    if(m!=2)
    {
    	exit(0);
    }
  }
  puts("I think i will see you again~");
}
int CheckIn()
{
  int v0; 
  int v1; 
  int buf;
  v0 = time(0);
  srand(v0);
  v1 = (rand() % 5);
  printf("enter:");
  scanf("%d",&buf);
  return buf == v1;
}

int init()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  memset(cd, 0, 65);
  return alarm(0x3C);
}
int main()
{
	init();
    tub();
	Crypto();
	if(check())
	{
		puts("OK,let us pwn pwn pwn!\n");
		xmsl();
		if(gg==0x77)
			vul();
		else
		{
			printf("you play CTF like cxk~\n");
			exit(0);
		}
	}
	else
	{
		printf("baby,try again?\n");
		exit(0);
	}
	return 0;
}