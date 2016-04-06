#include <cstdio>
const int maxn = 15;
int n, a[maxn];
bool dfs(int dep, int now)
{
	if(!now)
		return 1;
	if(dep == n)
		return 0;
	return dfs(dep + 1, now) || dfs(dep + 1, (now == -1 ? 0 : now) ^ a[dep]);
}
int main()
{
	for(int t = 0; t < 10; ++t)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		puts(!dfs(0, -1) ? "YES" : "NO");
	}
	return 0;
}
