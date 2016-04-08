#include <cstdio>
#include <cstring>
const int maxn = 101, maxm = 16;
int n, m, f[2][1 << maxm];
void upd(int &x, int y)
{
	if(x > y)
		x = y;
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(f[0], 0x3f, sizeof f[0]);
	f[0][0] = 0;
	for(int i = 1; i <= n; ++i)
	{
		int now = i & 1, last = now ^ 1, w;
		scanf("%d", &w);
		for(int s = 0; s < 1 << m; ++s)
			f[now][s] = f[last][s] + w;
		for(int j = 0; j < m; ++j)
		{
			scanf("%d", &w);
			for(int s = 0; s < 1 << m; ++s)
				if((s >> j) & 1)
					upd(f[now][s], f[now][s ^ (1 << j)] + w);
		}
		for(int s = 0; s < 1 << m; ++s)
			upd(f[now][s], f[last][s]);
	}
	printf("%d\n", f[n & 1][(1 << m) - 1]);
	return 0;
}
