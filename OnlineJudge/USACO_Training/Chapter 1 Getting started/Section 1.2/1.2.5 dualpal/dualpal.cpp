/*
ID: tangjin2
LANG: C++
TASK: dualpal
*/
#include <cstdio>
#include <cstring>
int num[36], len, n, s;
bool check()
{
	for(int i = 0; i <= len >> 1; ++i) if(num[i] != num[len - 1 - i]) return 0;
	return 1;
}
int main()
{
	freopen("dualpal.in", "r", stdin);
	freopen("dualpal.out", "w", stdout);
	scanf("%d%d", &n, &s);
	for(++s; n; ++s)
		for(int i = 2, j = s, flag = 0; i <= 10; ++i)
		{
			memset(num, 0, sizeof num);
			len = 0;
			while(j)
			{
				num[len++] = j % i;
				j /= i;
			}
			if(check()) ++flag;
			if(flag == 2)
			{
				printf("%d\n", s);
				--n;
				break;
			}
		}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
