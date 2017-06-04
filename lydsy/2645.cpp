#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 4001, maxm = 501, maxs = maxn * maxm;
int n, m, fa[maxn], c[maxn], st, pos[2][maxn], *P, ord[maxn];
int f[maxs], g[maxs], s[maxn], *F, ans;
std::vector<int> e[maxn];
inline void upd(int &x, int y)
{
	(x < y) && (x = y);
}
void dfs(int u)
{
	int *Fu = F + (P[u] = st);
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it, *Fv = F + (st += m);
		memcpy(Fv, Fu, m * sizeof(int));
		dfs(v);
		for(int i = 1, cst = c[v]; i < m; ++i)
			upd(Fu[i], Fv[i - 1] + cst);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	++m;
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", fa + i, c + i);
		if((--fa[i]) >= 0)
			e[fa[i]].push_back(i);
	}
	st = 0;
	P = pos[0];
	F = f;
	dfs(0);
	for(int i = 0; i < n; ++i)
		std::reverse(e[i].begin(), e[i].end());
	st = 0;
	P = pos[1];
	F = g;
	dfs(0);
	for(int i = 0; i < n; ++i)
		ord[P[i] / m] = i;
	for(int i = 0, ctr = 0; i < n; ++i, ctr += m)
	{
		int o = ord[i];
		s[o] = (fa[o] >= 0 ? s[fa[o]] : 0) + c[o];
		if(e[o].size() > 0)
			continue;
		int tmp = 0;
		for(int j = 0, x = pos[0][o] + m - 1, y = ctr; j < m; ++j, --x, ++y)
			upd(tmp, f[x] + g[y]);
		upd(ans, tmp + s[o]);
	}
	printf("%d\n", ans);
	return 0;
}
