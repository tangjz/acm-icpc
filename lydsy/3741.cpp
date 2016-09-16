#include <cstdio>
#include <cstring>
typedef unsigned long long ULL;
const int maxn = 50000, maxs = ((maxn - 1) >> 6) + 1, maxd = 4;
const char *buf = "ATCG";
int n, m, bsize, cur, pre = 1, ans;
char s[maxn + 1], t[maxn + 1];
ULL pos[maxd][maxs], f[3][maxs];
int main()
{
	scanf("%d%d%s%s", &n, &m, s, t);
	bsize = ((n - 1) >> 6) + 1;
	for(int i = 0; i < n; ++i)
		for(int o = 0; o < maxd; ++o)
			if(s[i] == buf[o])
				pos[o][i >> 6] |= 1ULL << (i & 63);
	// memset(f[cur], 0, bsize * sizeof(ULL));
	for(int i = 0; i < m; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		for(int o = 0; o < maxd; ++o)
			if(t[i] == buf[o])
				for(int j = 0; j < bsize; ++j)
					f[2][j] = f[pre][j] | pos[o][j];
		for(int j = 0, x = 1, y; j < bsize; ++j, x = y)
		{
			y = (f[pre][j] >> 63) & 1;
			f[pre][j] = f[pre][j] << 1 | x;
		}
		memcpy(f[cur], f[2], bsize * sizeof(ULL));
		for(int j = 0, x = 0, y; j < bsize; ++j, x = y)
		{
			y = f[cur][j] < f[pre][j] + x;
			f[cur][j] -= f[pre][j] + x;
			f[cur][j] = ~f[cur][j] & f[2][j];
		}
	}
	for(int i = 0; i < n; ++i)
		ans += (f[cur][i >> 6] >> (i & 63)) & 1;
	printf("%d\n", ans);
	return 0;
}
