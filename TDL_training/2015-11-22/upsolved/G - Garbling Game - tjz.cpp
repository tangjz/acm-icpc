#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 310, maxd = 110, BASE = 1000000000L, BASELEN = 9, mod = 100000;
int n, m, len, num[maxd], cnt[2][maxn * maxn], nxt[2][maxn * maxn], perm[maxn * maxn], pos[maxn * maxn], ans[maxn * maxn];
char tran[maxn][maxn + 1];
inline int idx(int x, int y)
{
	return x * m + y;
}
inline void mod_inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int divAndMod(int x)
{
	long long delta = 0;
	for(int i = len - 1; i > 0; --i)
	{
		delta += num[i];
		num[i] = delta / x;
		delta = delta % x * BASE;
	}
	delta += num[0];
	num[0] = delta / x;
	delta %= x;
	for( ; len > 1 && !num[len - 1]; --len);
	return (int)delta;
}
void transform(int counter, int cnt[])
{
	for(int i = 0, j = 0; counter--; j < m - 2 ? ++j : (++i, j = 0))
	{
		mod_inc(cnt[perm[idx(i, j)]], 1);
		if(tran[i][j] == 'L')
		{
			int tmp = perm[idx(i, j)];
			perm[idx(i, j)] = perm[idx(i, j + 1)];
			perm[idx(i, j + 1)] = perm[idx(i + 1, j + 1)];
			perm[idx(i + 1, j + 1)] = perm[idx(i + 1, j)];
			perm[idx(i + 1, j)] = tmp;
		}
		else if(tran[i][j] == 'R')
		{
			int tmp = perm[idx(i, j)];
			perm[idx(i, j)] = perm[idx(i + 1, j)];
			perm[idx(i + 1, j)] = perm[idx(i + 1, j + 1)];
			perm[idx(i + 1, j + 1)] = perm[idx(i, j + 1)];
			perm[idx(i, j + 1)] = tmp;
		}
	}
}
int main()
{
	bool flag = 0;
	while(scanf("%d%d%s", &n, &m, tran[0]) == 3)
	{
		if(flag)
			putchar('\n');
		else
			flag = 1;
		int slen = strlen(tran[0]);
		len = 0;
		for(int i = slen; i > 0; i -= 9)
		{
			int j = i - 9 < 0 ? 0 : i - 9;
			tran[0][i] = '\0';
			sscanf(tran[0] + j, "%d", num + (len++));
		}
		for(int i = 0; i < n - 1; ++i)
			scanf("%s", tran[i]);
		int res = divAndMod((n - 1) * (m - 1));
		for(int i = 0; i < n * m; ++i)
			perm[i] = i;
		memset(ans, 0, sizeof ans);
		if(len > 1 || num[0] > 0)
		{
			int cur = 0, pre = 1;
			memset(cnt[cur], 0, sizeof cnt[cur]);
			transform((n - 1) * (m - 1), cnt[cur]);
			for(int i = 0; i < n * m; ++i)
			{
				nxt[cur][perm[i]] = i;
				pos[i] = i;
			}
			for( ; len > 1 || num[0] > 0; divAndMod(2))
			{
				if(num[0] & 1)
					for(int i = 0; i < n * m; ++i)
					{
						mod_inc(ans[i], cnt[cur][pos[i]]);
						pos[i] = nxt[cur][pos[i]];
					}
				cur ^= 1;
				pre ^= 1;
				for(int i = 0; i < n * m; ++i)
				{
					cnt[cur][i] = cnt[pre][i];
					mod_inc(cnt[cur][i], cnt[pre][nxt[pre][i]]);
					nxt[cur][i] = nxt[pre][nxt[pre][i]];
				}
			}
			for(int i = 0; i < n * m; ++i)
				perm[pos[i]] = i;
		}
		transform(res, ans);
		for(int i = 0; i < n * m; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
