#include <cstdio>
const int maxn = 51, maxm = 8, maxs = 1 << 7, INF = 0x3f3f3f3f;
int n, m, msk2, all, bit[maxs], f[maxn][maxs], pos, cnt, ans[maxn];
long long msk1;
bool p[maxn][maxs];
char s[maxn], t[maxm];
int main()
{
	scanf("%d%d%s%s", &n, &m, s, t);
	for(int i = 0; i < n; ++i)
		msk1 |= (long long)(s[i] - '0') << i;
	for(int i = 0; i < m; ++i)
		msk2 |= (t[i] - '0') << i;
	while(~(msk2 >> m - 1) & 1)
	{
		msk1 &= ~(1LL << n - 1);
		--n;
		--m;
	}
	while(~msk2 & 1)
	{
		msk1 >>= 1;
		msk2 >>= 1;
		--n;
		--m;
	}
	all = (1 << m) - 1;
	for(int i = 1; i <= all; ++i)
		bit[i] = bit[i >> 1] + (i & 1);
	for(int i = 0; i <= all; ++i)
		f[m][i] = INF;
	f[m][msk1 & all] = bit[msk1 & all] * maxn;
	f[m][(msk1 & all) ^ msk2] = bit[(msk1 & all) ^ msk2] * maxn + 1;
	for(int i = m + 1; i <= n; ++i)
		for(int j = 0; j <= all; ++j)
		{
			f[i][j] = INF;
			int o = ((msk1 >> i - 1) & 1) ^ (j >> m - 1), last = ((o ? j ^ msk2 : j) << 1) & all, add = bit[j] - bit[last];
			for(int k = 0; k < 2; ++k)
				if(f[i - 1][last | k] != INF && f[i][j] > f[i - 1][last | k] + add * maxn + o)
				{
					f[i][j] = f[i - 1][last | k] + add * maxn + o;
					p[i][j] = k;
				}
		}
	for(int i = 1; i <= all; ++i)
		if(f[n][pos] > f[n][i])
			pos = i;
	for(int i = n; i >= m; --i)
	{
		int o = ((msk1 >> i - 1) & 1) ^ (pos >> m - 1);
		if(o)
			ans[cnt++] = i - m + 1;
		pos = ((o ? pos ^ msk2 : pos) << 1 | p[i][pos]) & all;
	}
	printf("%d\n", cnt);
	for(int i = cnt - 1; i >= 0; --i)
		printf("%d\n", ans[i]);
	return 0;
}
