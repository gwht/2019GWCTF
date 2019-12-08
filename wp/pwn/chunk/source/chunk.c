#include <stdio.h>
#include <stdlib.h>
char *chunk[10];
int number = 0; 
int *size[10];
int main(int argc, const char **argv, const char **envp)
{
  int v3;
  init();
  while ( 1 )
  {
    while ( 1 )
    {
      menu();
      scanf("%d", &v3);
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
  return memset(chunk, 0, 0x50uLL);
}
int add()
{
  int v0; 
  int v2; 
  int v3; 
  printf("Give me a book ID: ");
  scanf("%d", &v3);
  printf("how long: ", &v3);
  scanf("%d", &v2);
  if ( v3 >= 0 && v3 <= 9 && number <= 10 )
  {
    if(v2>=0&&v2<0x100)
    {
    v0 = v3;
    chunk[v0] = malloc(v2);
    size[v0] = v2;
    ++number;
    return puts("Done!\n");
    }
    else
    {
      puts("too large!");
    }
  }
}
int delete()
{
  int v1;
  unsigned int v2;
  v1 = 0;
  puts("Which one to throw?");
  scanf("%d", &v1);
  if ( v1 > 10 || v1 < 0 )
  {
    v2 = puts("Wrong!\n");
  }
  else
  {
    free(chunk[v1]);
    chunk[v1]=0;
    --number;
    v2 = puts("Done!\n");
  }
  return v2;
}
void show()
{
  char nptr;
  int v2;
  printf("Which book do you want to show?");
  read_0(&nptr, 16LL);
  v2 = atoi(&nptr);
  printf("Content: %s", chunk[v2]);
}
int edit()
{
  int idx;
  printf("Which book to write?");
  scanf("%d",&idx);
  printf("Content: ");
  read_0(chunk[idx], size[idx]);
  return puts("Done!\n");
}
int read_0(char *a1,int a2)
{
  int v3;
  char buf[10];
  int i = 0;
  for ( ; ; ++i )
  {
    v3 = i;
    if ( i >= a2 )
    	break;
    read(0, buf, 1);
    if ( *buf == 10 )
    	break;
    *(i + a1) = *buf;
  }
  *(i + a1) = 0;
  return v3;
}
int menu()
{
  puts("\n***********************");
  puts("Welcome to the magic book world!");
  puts("***********************");
  puts("1.create a book");
  puts("2.show the content");
  puts("3.throw a book");
  puts("4.write something on the book");
  puts("5.exit the world");
  return printf("Your choice: ");
}