#include <cstdio>
#include <algorithm>
const int maxn = 1002, dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
int t, n, mat[maxn][maxn], d[4][maxn][maxn];
int systim, bit[maxn], btim[maxn], tot, lnk[maxn], ltim[maxn], nxt[maxn], pos[maxn];
long long ans;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		ans = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= n; ++j)
				scanf("%d", mat[i] + j);
			mat[i][n + 1] = 0;
		}
		for(int j = 1; j <= n; ++j)
			mat[n + 1][j] = 0;
		for(int o = 0; o < 2; ++o)
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
					d[o][i][j] = mat[i][j] ? d[o][i + dx[o]][j + dy[o]] + 1 : 0;
		for(int o = 2; o < 4; ++o)
			for(int i = n; i >= 1; --i)
				for(int j = n; j >= 1; --j)
					d[o][i][j] = mat[i][j] ? d[o][i + dx[o]][j + dy[o]] + 1 : 0;
		for(int v = 1 - n; v <= n - 1; ++v)
		{
			++systim;
			tot = 0;
			int cnt = 0;
			// 1 + v <= i <= n + v
			for(int i = v > 0 ? v + 1 : 1, iR = v < 0 ? v + n : n, j = i - v; i <= iR; ++i, ++j)
			{
				if(mat[i][j])
				{
					++cnt;
					for(int x = i; x <= n; x += x & -x)
					{
						if(btim[x] != systim)
						{
							btim[x] = systim;
							bit[x] = 0;
						}
						++bit[x];
					}
					ans += cnt;
					for(int x = i - std::min(d[0][i][j], d[1][i][j]); x > 0; x -= x & -x)
						if(btim[x] == systim)
							ans -= bit[x];
					int k = i + std::min(d[2][i][j], d[3][i][j]) - 1;
					if(ltim[k] != systim)
					{
						ltim[k] = systim;
						lnk[k] = -1;
					}
					nxt[tot] = lnk[k];
					pos[tot] = i;
					lnk[k] = tot++;
				}
				for(int it = ltim[i] == systim ? lnk[i] : -1; it != -1; it = nxt[it])
				{
					--cnt;
					for(int x = pos[it]; x <= n; x += x & -x)
						--bit[x];
				}
			}
		}
		printf("Case %d: %I64d\n", Case, ans);
	}
	return 0;
}
