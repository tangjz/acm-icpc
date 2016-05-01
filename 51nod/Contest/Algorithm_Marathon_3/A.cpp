#include <cstdio>
const int maxn = 50;
int t, n, a[maxn], b[maxn];
bool dfs(int dep, int L, int R)
{
	if(dep == n)
		return L == R;
	b[L] = a[dep];
	return dfs(dep + 1, L + 1, R) || L > R && a[dep] == b[R] && dfs(dep + 1, L, R + 1);
}
int main()
{
	scanf("%d", &t);
	while(t-- > 0)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		b[0] = a[0];
		puts(dfs(1, 1, 0) ? "Good job!!" : "What a pity!");
		// bao jing le !!!
	}
	return 0;
}
