#include <cstdio>
const int maxn = 2000002;
int n, m;
char str[maxn];
bool flag1, flag2, flag3;
int main()
{
	scanf("%d%s", &n, str);
	if(~n & 1)
	{
		puts("NOT POSSIBLE");
		return 0;
	}
	m = n >> 1;
	for(int i = 0, j = 0; i <= m; ++i)
		if(str[i] != str[i + m + 1 - j])
			if(j)
			{
				flag1 = 1;
				break;
			}
			else
				j = 1;
	for(int i = 0, j = 0; i <= m; ++i)
		if(str[i - j] != str[i + m])
			if(j)
			{
				flag2 = 1;
				break;
			}
			else
				j = 1;
	if(flag1 && flag2)
		puts("NOT POSSIBLE");
	else if(flag1)
	{
		str[m] = '\0';
		puts(str);
	}
	else if(flag2)
		puts(str + m + 1);
	else
	{
		for(int i = 0; i < m; ++i)
			if(str[i] != str[i + m + 1])
			{
				flag3 = 1;
				break;
			}
		if(flag3)
			puts("NOT UNIQUE");
		else
			puts(str + m + 1);
	}
	return 0;
}
