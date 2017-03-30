#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
typedef long long LL;
const char *buf = "UDLR";
const int maxn = 100001, maxm = 400001, dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0};
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, x[maxn], y[maxn], ord[maxn], qtot, que[maxn], tot, lnk[maxn], pos[maxn];
char typ[maxn];
LL tim, dis[maxn];
struct Edge {
	int nxt, v, w;
} e[maxm];
std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int> >, std::greater<std::pair<LL, int> > > Q;
bool vis[maxn];
bool cmpx(int const &i, int const &j)
{
	return x[i] < x[j];
}
bool cmpy(int const &i, int const &j)
{
	return y[i] < y[j];
}
int main()
{
	scanf("%d%I64d", &n, &tim);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d %d %c", x + i, y + i, typ + i);
		ord[i] = i;
	}
	memset(lnk, -1, n * sizeof(int));
	memcpy(que, x, n * sizeof(int));
	std::sort(que, que + n);
	qtot = std::unique(que, que + n) - que;
	memset(pos, -1, qtot * sizeof(int));
	std::sort(ord, ord + n, cmpy);
	for(int i = 0; i < n; ++i) // y-plus
	{
		int o = ord[i], idx = std::lower_bound(que, que + qtot, x[o]) - que;
		if(pos[idx] != -1)
		{
			e[tot] = (Edge){lnk[pos[idx]], o, y[o] - y[pos[idx]]};
			lnk[pos[idx]] = tot++;
		}
		if(typ[o] == 'U')
			pos[idx] = o;
	}
	std::reverse(ord, ord + n);
	memset(pos, -1, qtot * sizeof(int));
	for(int i = 0; i < n; ++i) // y-minus
	{
		int o = ord[i], idx = std::lower_bound(que, que + qtot, x[o]) - que;
		if(pos[idx] != -1)
		{
			e[tot] = (Edge){lnk[pos[idx]], o, y[pos[idx]] - y[o]};
			lnk[pos[idx]] = tot++;
		}
		if(typ[o] == 'D')
			pos[idx] = o;
	}
	memcpy(que, y, n * sizeof(int));
	std::sort(que, que + n);
	qtot = std::unique(que, que + n) - que;
	memset(pos, -1, qtot * sizeof(int));
	std::sort(ord, ord + n, cmpx);
	for(int i = 0; i < n; ++i) // x-plus
	{
		int o = ord[i], idx = std::lower_bound(que, que + qtot, y[o]) - que;
		if(pos[idx] != -1)
		{
			e[tot] = (Edge){lnk[pos[idx]], o, x[o] - x[pos[idx]]};
			lnk[pos[idx]] = tot++;
		}
		if(typ[o] == 'R')
			pos[idx] = o;
	}
	std::reverse(ord, ord + n);
	memset(pos, -1, qtot * sizeof(int));
	for(int i = 0; i < n; ++i) // x-minus
	{
		int o = ord[i], idx = std::lower_bound(que, que + qtot, y[o]) - que;
		if(pos[idx] != -1)
		{
			e[tot] = (Edge){lnk[pos[idx]], o, x[pos[idx]] - x[o]};
			lnk[pos[idx]] = tot++;
		}
		if(typ[o] == 'L')
			pos[idx] = o;
	}
	memset(dis, 0x3f, n * sizeof(LL));
	dis[0] = 0;
	Q.push(std::make_pair(dis[0], 0));
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
		{
			int v = e[it].v;
			LL tmp = dis[u] + e[it].w;
			if(tmp < dis[v])
			{
				dis[v] = tmp;
				Q.push(std::make_pair(dis[v], v));
			}
		}
	}
	for(int i = 0; i < n; ++i)
	{
		LL rem = std::max(tim - dis[i], 0LL), xx = x[i], yy = y[i];
		for(int j = 0; buf[j]; ++j)
			if(typ[i] == buf[j])
			{
				xx += rem * dx[j];
				yy += rem * dy[j];
			}
		printf("%I64d %I64d\n", xx, yy);
	}
	return 0;
}
