// gcc -o fun misc.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void init()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
}
int main(int argc, char const *argv[])
{
	init();
	alarm(32);
	puts("Welcome go GWHT!");
	printf("Let's play rock-paper-scissors, if you can win me 32 times,you'll get the flag\n");
	char s[3]="rps";
	char kills[3]="psr";
	int i = 0;
	int flag = 0;
	char k;
	char killk;
	int num = 0;
	srand(time(NULL));
	while(i<32){
		int r = rand()%3;
		printf("This time I'll take %c,what's your choice\n",s[r]);
		if(flag == 0){
			k = s[r];
			killk = kills[r];
		}
		else if(flag == 1){
			k = s[(r+1)%3];
			killk = kills[(r+1)%3];
		}
		else if(flag == 2){
			k = s[(r+2)%3];
			killk = kills[(r+2)%3];
		}
		char input;
		scanf("%c",&input);
		getchar();
		if(input == killk){
			printf("You win!\n");
			num ++;
			flag = (flag+1)%3;
		}
		else{
			printf("You lose!\n");
			flag = 0;
		}
		i++;
	}
	if (num == 32)
	{
		printf("You get the flag:GWHT{n0t_b4d_g@Y}\n");
	}
	else{
		printf("bye bye!\n");
	}
	return 0;
}