#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 101, maxm = maxn * maxn << 2, mod = 1000000007;
int t, n, totx, quex[maxn << 1], toty, quey[maxn << 1], totp;
int row[maxm], col[maxm], sqr[maxm], delta;
int pre = 1, cur, tot[2], fa[maxm];
struct Query
{
	int x1, y1, x2, y2, c;
} query[maxn];
struct Edge
{
	int u, v, w;
} edges[2][maxn * maxn << 2];
int find(int x)
{
	return fa[x] < 0 ? x : fa[x] = find(fa[x]);
}
bool merge(int u, int v)
{
	u = find(u);
	v = find(v);
	if(u == v)
		return 0;
	if(fa[u] < fa[v])
		fa[v] = u;
	else if(fa[u] > fa[v])
		fa[u] = v;
	else
	{
		fa[v] = u;
		--fa[u];
	}
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		totx = toty = 0;
		for(int i = 0; i < n; ++i)
		{
			int &x1 = query[i].x1, &y1 = query[i].y1, &x2 = query[i].x2, &y2 = query[i].y2, &c = query[i].c;
			scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &c);
			quex[totx++] = x1;
			quey[toty++] = y1;
			quex[totx++] = x2;
			quey[toty++] = y2;
		}
		std::sort(quex, quex + totx);
		totx = std::unique(quex, quex + totx) - quex;
		std::sort(quey, quey + toty);
		toty = std::unique(quey, quey + toty) - quey;
		totp = totx * toty;
		memset(row, 0, totp * sizeof(int));
		memset(col, 0, totp * sizeof(int));
		memset(sqr, 0, totp * sizeof(int));
		delta = tot[cur] = 0;
		for(int o = 0; o < n; ++o)
		{
			int x1 = std::lower_bound(quex, quex + totx, query[o].x1) - quex;
			int y1 = std::lower_bound(quey, quey + toty, query[o].y1) - quey;
			int x2 = std::lower_bound(quex, quex + totx, query[o].x2) - quex;
			int y2 = std::lower_bound(quey, quey + toty, query[o].y2) - quey;
			int c = query[o].c, ans = 0, pos;
			pre ^= 1;
			cur ^= 1;
			tot[cur] = 0;
			memset(fa, -1, totp * sizeof(int));
			for(pos = 0; pos < tot[pre] && edges[pre][pos].w > c; ++pos)
			{
				merge(edges[pre][pos].u, edges[pre][pos].v);
				if((ans += edges[pre][pos].w) >= mod)
					ans -= mod;
				edges[cur][tot[cur]++] = edges[pre][pos];
			}
			for(int x = x1; x <= x2; ++x)
				for(int y = y1, idx = x * toty + y; y <= y2; ++y, ++idx)
				{
					if(x < x2)
					{
						if(row[idx] < c)
						{
							delta = (delta + (LL)(quex[x + 1] - quex[x] - 1) * (c - row[idx])) % mod;
							row[idx] = c;
						}
						if(merge(idx, idx + toty))
						{
							if((ans += c) >= mod)
								ans -= mod;
							edges[cur][tot[cur]++] = (Edge){idx, idx + toty, c};
						}
					}
					if(y < y2)
					{
						if(col[idx] < c)
						{
							delta = (delta + (LL)(quey[y + 1] - quey[y] - 1) * (c - col[idx])) % mod;
							col[idx] = c;
						}
						if(merge(idx, idx + 1))
						{
							if((ans += c) >= mod)
								ans -= mod;
							edges[cur][tot[cur]++] = (Edge){idx, idx + 1, c};
						}
					}
					if(x < x2 && y < y2 && sqr[idx] < c)
					{
						delta = (delta + (LL)(quex[x + 1] - quex[x] - 1) * (quey[y + 1] - quey[y] - 1) % mod * (c - sqr[idx])) % mod;
						sqr[idx] = c;
					}
				}
			for( ; pos < tot[pre]; ++pos)
				if(merge(edges[pre][pos].u, edges[pre][pos].v))
				{
					if((ans += edges[pre][pos].w) >= mod)
						ans -= mod;
					edges[cur][tot[cur]++] = edges[pre][pos];
				}
			if((ans += delta) >= mod)
				ans -= mod;
			printf("%d\n", ans);
		}
	}
	return 0;
}
