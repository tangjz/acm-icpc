/*
ID: tangjin2
LANG: C++
TASK: namenum
*/
#include <cstdio>
#include <cstring>
const char transform[10][3] = {{}, {}, {'A', 'B', 'C'}, {'D', 'E', 'F'}, {'G', 'H', 'I'}, {'J', 'K', 'L'}, {'M', 'N', 'O'}, {'P', 'R', 'S'}, {'T', 'U', 'V'}, {'W', 'X', 'Y'}};
char name[13];
int num[13], key, flag;
void find(int dep)
{
	if(dep == key)
	{
		if(name[dep] == '\0') puts(name), flag = 1;
		return;
	}
	if(name[dep] >= transform[num[dep]][0] && name[dep] <= transform[num[dep]][2] && name[dep] != 'Q' && name[dep] != 'Z') find(dep + 1);
}
int main()
{
	freopen("namenum.in", "r", stdin);
	freopen("namenum.out", "w", stdout);
	char ch;
	while(scanf("%c", &ch) != EOF) if(ch != '\n') num[key++] = ch - '0';
	fclose(stdin);
	freopen("dict.txt", "r", stdin);
	gets(name);
	while(name[0] <= transform[num[0]][2])
	{
		find(0);
		gets(name);
	}
	if(!flag) puts("NONE");
	fclose(stdin);
	fclose(stdout);
	return 0;
}
