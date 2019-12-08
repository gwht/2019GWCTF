// g++ -s -m32 -fno-stack-protector -o easy_pwn easy_pwn.cpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <unistd.h>
using namespace std;
string input;
//字符串分割函数
vector<string> split(string str,string pattern)
{
    string::size_type pos;
    vector<string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}
string I = "I";

void func()
{
	char s[0x20];
    memset(s,0,0x20);
    printf("%s\n","Hello,please tell me your name!");
	// fgets(s,0x20,stdin);
	read(0,s,0x20);
	input = "";
	input.operator+=(s);
	
	vector<string> result = split(input,I);
	if(result.size() > 1){
		input = "";
        if(result[0] != "")
            input.operator+=(result[0]);
		for(int i=1;i<result.size();i++){
			input.operator+=("pretty");
			input.operator+=(result[i]);
		}
	}
	strcpy(s,input.c_str());
	printf("Bye!%s",s);
}

int main()
{
	setvbuf(stdout, 0, 2, 0);
  	setvbuf(stdin, 0, 2, 0);
  	setvbuf(stderr, 0, 2, 0);
	alarm(30);
	func();
	return 0;
}