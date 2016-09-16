#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1001, maxm = 30001;
int n, m, S, T, lnk[maxn], val[maxm], ptot, path[maxn], idx, ans, out[3];
int que[maxn], pre[maxn], L, R, tot;
int bcnt, bno[maxn], lnk2[maxn], val2[maxm];
struct Edge
{
	int nxt, v;
} e[maxm << 1], e2[maxm << 1];
bool vis[maxn], bri[maxm];
int tarjan(int u, int Fa)
{
	int lowu = pre[u] = ++tot;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		if(Fa == (it ^ 1) || (it >> 1) == idx)
			continue;
		int &v = e[it].v;
		if(pre[v] == -1)
		{
			int lowv = tarjan(v, it);
			if(lowu > lowv)
				lowu = lowv;
			if(pre[u] < lowv)
				bri[it >> 1] = 1;
		}
		else if(lowu > pre[v])
			lowu = pre[v];
	}
	return lowu;
}
void dfs(int u)
{
	bno[u] = bcnt;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(!bri[it >> 1] && bno[e[it].v] == -1 && (it >> 1) != idx)
			dfs(e[it].v);
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &S, &T);
	--S, --T;
	memset(lnk, -1, n * sizeof(int));
	for(int i = 0; i < m; ++i)
	{
		int u, v;
		scanf("%d%d%d", &u, &v, val + i);
		--u, --v;
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	vis[S] = 1;
	for(int it = lnk[S]; it != -1 && !vis[T]; it = e[it].nxt)
		if(!vis[e[it].v])
		{
			pre[R] = -1;
			que[R++] = it;
			vis[e[it].v] = 1;
		}
	for( ; L < R && !vis[T]; ++L)
	{
		int u = e[que[L]].v;
		for(int it = lnk[u]; it != -1 && !vis[T]; it = e[it].nxt)
			if(!vis[e[it].v])
			{
				pre[R] = L;
				que[R++] = it;
				vis[e[it].v] = 1;
			}
	}
	if(!R || e[que[R - 1]].v != T)
	{
		puts("0\n0");
		return 0;
	}
	for(int o = R - 1; o != -1; o = pre[o])
		path[ptot++] = que[o] >> 1;
	ans = ~0u >> 1;
	for(int o = 0; o < ptot; ++o)
	{
		idx = path[o];
		tot = 0;
		memset(vis, 0, n * sizeof(bool));
		memset(pre, -1, n * sizeof(int));
		memset(bri, 0, n * sizeof(bool));
		tarjan(S, -1);
		if(pre[T] == -1)
		{
			if(ans > val[idx])
			{
				ans = val[idx];
				out[0] = 1;
				out[1] = idx + 1;
			}
			continue;
		}
		bcnt = 0;
		memset(bno, -1, n * sizeof(int));
		for(int i = 0; i < n; ++i)
			if(pre[i] != -1 && bno[i] == -1)
			{
				dfs(i);
				++bcnt;
			}
		if(bno[S] == bno[T])
			continue;
		tot = 0;
		memset(lnk2, -1, bcnt * sizeof(int));
		for(int i = 0; i < m; ++i)
			if(bri[i])
			{
				int u = bno[e[i << 1].v], v = bno[e[i << 1 | 1].v];
				e2[tot << 1] = (Edge){lnk2[u], v};
				lnk2[u] = tot << 1;
				e2[tot << 1 | 1] = (Edge){lnk2[v], u};
				lnk2[v] = tot << 1 | 1;
				val2[tot++] = i;
			}
		memset(vis, 0, bcnt * sizeof(bool));
		L = R = 0;
		vis[bno[S]] = 1;
		for(int it = lnk2[bno[S]]; it != -1 && !vis[bno[T]]; it = e2[it].nxt)
			if(!vis[e2[it].v])
			{
				pre[R] = -1;
				que[R++] = it;
				vis[e2[it].v] = 1;
			}
		for( ; L < R && !vis[bno[T]]; ++L)
		{
			int u = e2[que[L]].v;
			for(int it = lnk2[u]; it != -1 && !vis[bno[T]]; it = e2[it].nxt)
				if(!vis[e2[it].v])
				{
					pre[R] = L;
					que[R++] = it;
					vis[e2[it].v] = 1;
				}
		}
		for(int o = R - 1; o != -1; o = pre[o])
			if(ans > val[idx] + val[val2[que[o] >> 1]])
			{
				ans = val[idx] + val[val2[que[o] >> 1]];
				out[0] = 2;
				out[1] = idx + 1;
				out[2] = val2[que[o] >> 1] + 1;
				if(out[1] > out[2])
				{
					out[1] = out[1] + out[2];
					out[2] = out[1] - out[2];
					out[1] = out[1] - out[2];
				}
			}
	}
	if(ans == (int)(~0u >> 1))
	{
		puts("-1");
		return 0;
	}
	printf("%d\n%d\n", ans, out[0]);
	for(int i = 1; i <= out[0]; ++i)
		printf("%d%c", out[i], " \n"[i == out[0]]);
	return 0;
}
