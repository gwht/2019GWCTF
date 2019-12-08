#include <stdio.h>
#include <stdlib.h>
char *chunk[10];
int *size[10];
int main(int argc, const char **argv, const char **envp)
{
  int v3;
  init();
  while ( 1 )
  {
    while ( 1 )
    {
      qume();
      menu();
      v3 = read_1();
      if ( v3 != 1 )
        break;
      add();
    }
    if ( v3 == 3 )
    {
      delete();
    }
    else if ( v3 == 2 )
    {
      show();
    }
    else if ( v3 == 4 )
    {
      edit();
    }
    else
    {
      if ( v3 == 5 )
      {
        puts("See you tomorrow~");
        exit(0);
      }
      puts("Invalid choice!");
    }
  }
}
int init()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  memset(chunk, 0, 0x50);
  memset(size, 0, 0x50);
  return alarm(0x3C);
}
int add()
{
  int v2; 
  int v3; 
  printf("Which basketball do you want?");
  v3 = read_1();
  if ( v3 >= 0 && v3 < 5)
  {
  	printf("how big: ");
  	v2 = read_1();
  	if(v2>0x90 && v2<=0x400)
  	{
  		chunk[v3] = malloc(v2);
  		size[v3] = v2;
  	}
  	else
  	{
  		puts("Wrong size!");
  	}
  }
  else
  {
  	puts("Wrong index!");

  }
  return puts("Done!\n");
}
int delete()
{
  int v1;
  int v2;
  puts("Which one you do not want?");
  v1 = read_1();
  if ( v1>=0 && v1<5 )
  {
    if(chunk[v1])
  	{
  		free(chunk[v1]);
  		chunk[v1] = 0;
  		size[v1] = 0;
        v2 = puts("Done!\n");
    }
    else
    {
    	v2 = puts("Wrong!\n");
    }
  }
  else
  {
  	v2 = puts("Wrong idx!\n");
  }
  return v2;
}
void show()
{
	puts("May I give you a true address?");
    puts("\xF0\x9F\x92\xA9");
}
int edit()
{
  int idx;
  printf("Which basketball to write?");
  idx = read_1();
  if ( idx >=0 && idx <5 && chunk[idx] )
  {
  	printf("Signature: ");
  	read_0(chunk[idx], size[idx]);
  }
  else
  {
  	puts("Wrong!\n");
  }
  return puts("Done!\n");
}
int read_0(char *a1,int a2)
{
  int v3;
  char buf[10];
  for (int i = 0; ; ++i )
  {
    v3 = i;
    if ( i > a2 )
    	break;
    read(0, buf, 1);
    if ( *buf == 10 )
    	break;
    *(i + a1) = *buf;
    if(i == a2)
    {
    	*(i + a1) = 0;
    }
  }
  return v3;
}
void qume()
{
	puts("=========================Chicken-you-are-too-beautiful!=========================");
	puts("|                                                                              |");
	puts("|                                       `'`                                    |");
	puts("|                                   `:!$$$|'                                   |");
	puts("|                                .:||:`'|$$!`                                  |");
	puts("|                                .:|;'```;!`                                   |");
	puts("|                                  .'';:';:.                                   |");
	puts("|                                    `;|&@@@%;|%;'.                            |");
	puts("|                                `%@|!&@@&&@||@@@@@@@&&$!`                     |");
	puts("|                        `:`..:$@@@@&|%@&@@@%|&@@@@@@@@@@&$:                   |");
	puts("|                 `!%!!%&@@@@@@@@@@@@%|&@@@@@||@@@@%:::;;::'.                  |");
	puts("|                `:'''''';||$$$|;:''|@||@@@@@&|%@@@%`   .`..                   |");
	puts("|               .'::::;;;;'         .!$|$@@@@@&|$@@@|.                         |");
	puts("|                '!!!!!!!!`           :|%&@@@@@&|$@@@|.                        |");
	puts("|                 .:!|||:.             .`!&@@@@@&|%@@@!                        |");
	puts("|                                         '|$&@@&$$$%|`                        |");
	puts("|                                       .:!!|||||!!!!!'                        |");
	puts("|                                       `;;!!!!!!!!!!!'                        |");
	puts("|                                      .';!!!!!!!!!!!!'                        |");
	puts("|                                      ';;!!|$$||!!!!;`                        |");
	puts("|                                     .';;!!|$$||!!!!:.                        |");
	puts("|                                     .:;;;!|;';!;!!;`                         |");
	puts("|                                     .:;;!|:..:!!!!'                          |");
	puts("|                                     `;!!|!` .:!!!!`                          |");
	puts("|                                     :||$$:  .:!!||!'                         |");
	puts("|.....................................`:||%|:. .'!|||!:........................|");
	puts("|```````````````````````````````````````:|$$!'````:|$&&!```````````````````````|");
	puts("|````````````````````````````````````````:||%!'`````!&&%:``````````````````````|");
	puts("|`````````````````````````````````````````:|%$|'````;$$$!``````````````````````|");
	puts("|``````````````````````````````````````````!&@&!````'|&|:``````````````````````|");
	puts("|````````````````````````````````````````;%$&@@%'``````````````````````````````|");
	puts("================================================================================");
}
int menu()
{
  puts("***********************");
  puts("CXK play CTF!");
  puts("***********************");
  puts("1.Buy a basketball");
  puts("2.Show the wondeful skill");
  puts("3.Throw the basketball");
  puts("4.Write your signature");
  puts("5.Go home");
  puts("***********************");
  return printf("Your choice: ");
}
int read_1()
{
  int v3;
  char nptr[10];
  read_0(nptr,0x10);
  v3 = atoi(nptr);
}
