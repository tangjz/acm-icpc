#include <stdio.h>
const int maxn = 17;
int n, ban[maxn], ans;
void dfs(int dep, int col, int rc, int cr)
{
	if(dep == n)
	{
		++ans;
		return;
	}
	int msk = ~(ban[dep] | col | rc | cr) & ((1 << n) - 1);
	while(msk > 0)
	{
		int lbt = msk & -msk;
		dfs(dep + 1, col | lbt, (rc | lbt) >> 1, (cr | lbt) << 1);
		msk ^= lbt;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
		{
			int x;
			scanf("%d", &x);
			ban[i] |= x << j;
		}
	dfs(0, 0, 0, 0);
	printf("%d\n", ans);
	return 0;
}
