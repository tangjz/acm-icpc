#include <stdio.h>
const int maxn = 3, INF = ~0u >> 1;
int t, val[maxn + 1];
char op[maxn];
bool dfs(int dep, int last, int sum)
{
	if(dep == maxn)
		return last != INF && last == sum;
	if(last == INF || last == sum)
	{
		op[dep] = '=';
		if(dfs(dep + 1, sum, val[dep + 1]))
			return 1;
	}
	op[dep] = '+';
	if(dfs(dep + 1, last, sum + val[dep + 1]))
		return 1;
	op[dep] = '-';
	if(dfs(dep + 1, last, sum - val[dep + 1]))
		return 1;
	return 0;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		for(int i = 0; i <= maxn; ++i)
			scanf("%d", val + i);
		dfs(0, INF, val[0]);
		printf("Case #%d: %d", Case, val[0]);
		for(int i = 0; i < maxn; ++i)
			printf(" %c %d", op[i], val[i + 1]);
		putchar('\n');
	}
	return 0;
}
