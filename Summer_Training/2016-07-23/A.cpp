#include <bitset>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
const int maxn = 256;
int t, n, m, kk, tot, cur, pre = 1;
char str[maxn + 1][maxn + 1];
std::pair<int, int> a[maxn];
std::bitset<maxn + 1> f[maxn << 1], g[2][maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d", &n, &m, &kk);
		for(int i = 0; i < n; ++i)
			scanf("%s", str[i]);
		for(int i = 0; i < kk; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[i] = std::make_pair(--x, --y);
		}
		std::sort(a, a + kk);
		for(int i = 0; i < m; ++i)
		{
			a[kk++] = std::make_pair(n, i);
			str[n][i] = 'W';
		}
		tot = 0;
		for(int i = 0; i < m; ++i)
		{
			g[pre][i].reset();
			g[cur][i].reset();
			g[cur][i].set(i);
		}
		for(int i = 0, j = 0; i <= n; ++i)
		{
			for( ; j < kk && a[j].first == i; ++j)
				f[tot++] = g[cur][a[j].second];
			if(i == n)
				break;
			pre ^= 1;
			cur ^= 1;
			for(int j = 0; j < m; ++j)
			{
				g[cur][j] ^= g[pre][j];
				if(j)
					g[cur][j] ^= g[pre][j - 1];
				if(j + 1 < m)
					g[cur][j] ^= g[pre][j + 1];
				if(str[i][j] == 'B')
					g[cur][j].flip(m);
			}
		}
		bool flag = 1;
		int r = 0;
		for(int i = 0; i < m; ++i)
		{
			int k = -1;
			for(int j = r; j < tot; ++j)
				if(f[j].test(i))
				{
					k = j;
					break;
				}
			if(k == -1)
				continue;
			std::swap(f[r], f[k]);
			for(int j = i + 1; j < tot; ++j)
				if(f[j].test(i))
					f[j] ^= f[i];
			++r;
		}
		for(int i = r; i < tot; ++i)
			if(f[i].test(m))
			{
				flag = 0;
				break;
			}
		printf("Case #%d:\n%s\n", Case, flag ? "YES" : "NO");		
	}
	return 0;
}
