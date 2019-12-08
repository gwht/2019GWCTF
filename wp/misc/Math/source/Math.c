#include <string.h>
#include <stdio.h>
int main()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  char buf[0x100];
  int v0; 
  int v1;
  int v2;
  int v3;
  int v4;
  int v8;
  int v10;
  int i=0;
  v0 = time(0);
  srand(v0);
  do
  {
  alarm(5);
  v1 = (rand() % 200);
  v2 = (rand() % 200);
  v8 = (rand() % 200);
  v10 = (rand() % 200);
  puts("Pass 150 levels and i will give you the flag~");
  puts("====================================================");
  printf("Now level %d\n", i);
  printf("Math problem: %d * %d - %d + %d = ??? ", v1, v2, v8, v10);
  puts("Give me your answer:");
  read(0, &buf, 0x80);
  v4 = v1 * v2 - v8 + v10;
  v3 = strtol(&buf, 0LL, 10);
  if(v3==v4)
  {
  	puts("Right! Continue~");
  	i = i + 1;
  	sleep(0.1);
  }
  else
  {
  	puts("Try again?");
  	exit(0);
  }
  }
  while(i<150);
  if(i==150)
  {
  	puts("Congratulation!");
  	system("/bin/sh\x00");
  }
  else
  {
  	puts("Wrong!");
  	exit(0);
  }
}