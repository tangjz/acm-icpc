#include <cstdio>
#include <algorithm>
const int maxn = 12, mod = 1000000000;
int n, m, f[2][1 << maxn], cur, pre = 1;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < 1 << m; ++i)
		f[cur][i] = 1;
	for(int i = 0; i < n; ++i)
	{
		int mask = 0;
		for(int j = 0, x; j < m; ++j)
		{
			scanf("%d", &x);
			mask |= x << j;
		}
		cur ^= 1;
		pre ^= 1;
		for(int j = 0; j < 1 << m; ++j)
			f[cur][j] = (j & mask) == j && !(j & (j >> 1)) ? f[pre][j] : 0;
		for(int j = 0; j < m; ++j)
			for(int k = 0; k < 1 << m; ++k)
				if((k & (1 << j)) && (f[cur][k] += f[cur][k ^ (1 << j)]) >= mod)
					f[cur][k] -= mod;
		std::reverse(f[cur], f[cur] + (1 << m));
	}
	printf("%d\n", f[cur][0]);
	return 0;
}
