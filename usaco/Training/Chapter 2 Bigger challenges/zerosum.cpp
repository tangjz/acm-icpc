/*
ID: tangjin2
LANG: C++
TASK: zerosum
*/
#include <cstdio>
const int maxn = 10;
int n, seq[maxn];
void dfs(int dep, int sum, int num)
{
	if(dep == n)
	{
		if(sum + num == 0)
		{
			putchar('1');
			for(int i = 1; i < n; ++i)
				printf("%c%d", "- +"[seq[i] + 1], i + 1);
			putchar('\n');
		}
		return;
	}
	seq[dep] = 0;
	dfs(dep + 1, sum, num * 10 + (num < 0 ? -dep - 1 : dep + 1));
	seq[dep] = 1;
	dfs(dep + 1, sum + num, dep + 1);
	seq[dep] = -1;
	dfs(dep + 1, sum + num, -dep - 1);
}
int main()
{
	freopen("zerosum.in", "r", stdin);
	freopen("zerosum.out", "w", stdout);
	scanf("%d", &n);
	dfs(1, 0, 1);
	return 0;
}
