/*
ID: tangjin2
LANG: C++
TASK: hamming
*/
#include <cstdio>
int n, b, d, maxval, ans[64];
bool check(int x, int y)
{
	int cnt = 0;
	while(x || y)
	{
		if((x & 1) != (y & 1)) ++cnt;
		x >>= 1;
		y >>= 1;
	}
	if(cnt >= d) return 1;
	return 0;
}
bool compare(int x, int dep)
{
	while(dep) if(!check(x, ans[--dep])) return 0;
	return 1;
}
void dfs(int dep, int from)
{
	if(dep == n) return;
	for(int i = from + 1; i < maxval; ++i)
		if(compare(i, dep))
		{
			ans[dep] = i;
			dfs(dep + 1, i);
			return;
		}
}
int main()
{
	freopen("hamming.in", "r", stdin);
	freopen("hamming.out", "w", stdout);
	scanf("%d%d%d", &n, &b, &d);
	maxval = 1 << b;
	dfs(1, 0);
	for(int i = 0; i < n - 1; ++i)
	{
		printf("%d", ans[i]);
		putchar(i % 10 == 9 ? '\n' : ' ');
	}
	printf("%d\n", ans[n - 1]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
