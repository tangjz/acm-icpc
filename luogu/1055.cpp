#include <cstdio>
int ans;
char ch[15];
int main()
{
	gets(ch);
	for(int i = 1, j = 0; i <= 9; ++i, ++j)
	{
		while(ch[j] < '0' || ch[j] > '9') ++j;
		ans += i * (ch[j] - '0');
	}
	ans %= 11;
	ans = ans == 10 ? 'X' : ans + '0';
	if(ch[12] == ans) puts("Right");
	else ch[12] = ans, puts(ch);
}