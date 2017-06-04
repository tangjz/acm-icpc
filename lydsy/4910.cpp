#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 20001, maxm = 500001, maxs = 25020001;
int t, n, m, fa[maxn], c[maxn], w[maxn], st, pos[2][maxn], *P, ord[maxn];
int f[maxs], g[maxs], s[maxn], *F, stg;
std::vector<int> e[maxn];
inline void upd(int &x, int y)
{
	(x < y) && (x = y);
}
inline void modify(int *dst, int *src, int upp, int cst)
{
	int L = 0, R = 0;
	static int que[maxm][2];
	for(int i = 0, idx = -upp, v = 0; i < m; ++i, ++idx, v += cst)
	{
		(L < R && que[L][0] < idx) && (++L);
		int tmp = src[i] - v;
		(L < R) && (upd(dst[i], que[L][1] + v), 0);
		for( ; L < R && que[R - 1][1] <= tmp; --R);
		que[R][0] = i;
		que[R++][1] = tmp;
	}
}
void dfs(int u)
{
	int *Fu = F + (P[u] = st);
	if(stg == 0 && c[u] > 1) // 2??? -> 2????¨² 
		modify(Fu, Fu, c[u] - 1, w[u]);
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it, *Fv = F + (st += m);
		memcpy(Fv, Fu, m * sizeof(int));
		dfs(v);
		if(stg == 0) // 2????¨² -> ???¨² 
			modify(Fu, Fv, 1, w[v]);
		else // 2??? -> ???¨² 
			modify(Fu, Fv, c[v], w[v]);
	}
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		++m;
		for(int i = 0; i < n; ++i)
			std::vector<int>().swap(e[i]);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d", fa + i, c + i, w + i);
			if((--fa[i]) >= 0)
				e[fa[i]].push_back(i);
		}
		st = 0;
		P = pos[0];
		F = f;
		stg = 0; // ?¨´?¡ã¨°?¨¦?2????¨² 
		memset(F, 0, m * sizeof(int));
		dfs(0);
		for(int i = 0; i < n; ++i)
			std::reverse(e[i].begin(), e[i].end());
		st = 0;
		P = pos[1];
		F = g;
		stg = 1; // ?¨´?¡ã¨°?¨¦?2??? 
		memset(F, 0, m * sizeof(int));
		dfs(0);
		for(int i = 0; i < n; ++i)
			ord[P[i] / m] = i;
		int ans = 0;
		for(int i = 0, ctr = 0; i < n; ++i, ctr += m)
		{
			int o = ord[i];
			s[o] = (fa[o] >= 0 ? s[fa[o]] : 0) + w[o];
			if(e[o].size() > 0)
				continue;
			int tmp = 0;
			for(int j = 0, x = pos[0][o] + m - 1, y = ctr; j < m; ++j, --x, ++y)
				upd(tmp, f[x] + g[y]);
			upd(ans, tmp + s[o]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
