#include <stdio.h>
#include <algorithm>
const int maxn = 501;
int n, f[2][maxn], cur, nxt = 1, ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i, cur ^= 1, nxt ^= 1)
		for(int j = 1; j <= i; ++j)
		{
			scanf("%d", f[nxt] + j);
			f[nxt][j] += std::max(f[cur][j - 1], f[cur][j]);
		}
	for(int i = 1; i <= n; ++i)
		if(ans < f[cur][i])
			ans = f[cur][i];
	printf("%d\n", ans);
	return 0;
}
