
#include <stdio.h>
#include <sys/prctl.h>
#include <linux/seccomp.h>
#include <linux/filter.h>
void set_secommp(){
    prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
    struct sock_filter sfi[] ={
        {0x20,0x00,0x00,0x00000004},
        {0x15,0x00,0x05,0xc000003e},
        {0x20,0x00,0x00,0x00000000},
        {0x35,0x00,0x01,0x40000000},
        {0x15,0x00,0x02,0xffffffff},
        {0x15,0x01,0x00,0x0000003b},
        {0x06,0x00,0x00,0x7fff0000},
        {0x06,0x00,0x00,0x00000000}
    };
    struct sock_fprog sfp = {8, sfi};
    prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &sfp);
}

int is_printable(char *s){
	for (int i = 0; i < strlen(s); ++i)
	{
		if (s[i] < 0x20 || s[i] > 0x7e)
		{
			return 0;
		}
	}
	return 1;
}
int init()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  return alarm(0x3C);
}

int main(int argc, char const *argv[])
{
	init();
	set_secommp();
	char input[100];
	bzero(input,104); 
	printf("Welcome,tell me your name:\n");
	input[read(0,input,100)-1] = 0;
	if (is_printable(input))
	{
		((void (*)(void))input)();
	}
	else
	{
		printf("It must be a printable name!\n");
	}
	return 0;
}