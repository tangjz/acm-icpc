#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 2610, maxm = 1300000, maxs = 1024;
int n, n1, n2, m, N, M, S, T, lnk[maxn], level[maxn], que[maxn], L, R;
struct Edge
{
	int nxt, v, f;
} e[maxm << 1];
std::map<std::string, int> Hash;
char str[maxs];
void addEdge(int u, int v, int c)
{
	e[M] = (Edge){lnk[u], v, c};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0};
	lnk[v] = M++;
}
bool bfs()
{
	L = R = 0;
	memset(level, 0, N * sizeof(int));
	level[S] = 1;
	que[R++] = S;
	while(L < R)
	{
		int u = que[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].f && !level[e[it].v])
			{
				level[e[it].v] = level[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return level[T];
}
int dfs(int u, int lim)
{
	if(u == T || !lim)
		return lim;
	int ret = 0;
	for(int it = lnk[u], tmp; it != -1; it = e[it].nxt)
		if(e[it].f && level[e[it].v] == level[u] + 1
		&& (tmp = dfs(e[it].v, std::min(e[it].f, lim - ret))))
		{
			e[it].f -= tmp;
			e[it ^ 1].f += tmp;
			ret += tmp;
		}
	if(!ret)
		level[u] = 0;
	return ret;
}
int main()
{
	while(scanf("%d%d%d%d", &n, &n1, &n2, &m) == 4)
	{
		N = n + m * 2 + 2;
		M = 0;
		S = N - 2;
		T = N - 1;
		memset(lnk, -1, N * sizeof(int));
		std::map<std::string, int>().swap(Hash);
		for(int i = 0; i < n1; ++i)
		{
			scanf("%s", str);
			Hash[str] = i;
			addEdge(S, i, 1);
		}
		n2 += n1;
		for(int i = n1; i < n2; ++i)
		{
			scanf("%s", str);
			Hash[str] = i;
			addEdge(i, T, 1);
		}
		for(int i = 0; i < m; ++i)
		{
			int cnt = 0, idx;
			scanf("%d", &cnt);
			while(cnt--)
			{
				scanf("%s", str);
				if(!Hash.count(str))
					idx = Hash[str] = n2++;
				else
					idx = Hash[str];
				addEdge(idx, n + i, 1);
				addEdge(n + m + i, idx, 1);
			}
			addEdge(n + i, n + m + i, 1);
		}
		int flow = 0;
		while(bfs())
			for(int tmp; (tmp = dfs(S, maxn)); flow += tmp);
		printf("%d\n", flow);
	}
	return 0;
}
