#include <stdio.h>
void init()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
}
void fun1(){
	char input[0x100];
	char tmp;
	int i = 0;
	while(!feof(stdin)){
		tmp = fgetc(stdin);
		if(tmp == '\n')
			break;
		input[i++] = tmp;
	}
	input[i] = 0;
}

int main(int argc, char const *argv[])
{
	init();
	alarm(0x30);
	printf("Hack 4 fun!\n");
	fun1();
	return 0;
}