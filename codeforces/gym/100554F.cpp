#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 51, maxm = 50001, mod = 1000000007;
int t, n, mx, l[maxn], r[maxn], mu[maxm];
int f[maxn][maxm], g[maxn][maxm], h[maxn][maxm];
int pre[maxn][maxm], suf[maxn][maxm];
vector<int> e[maxn];
inline void mod_inc(int &x, int y)
{
	if((x += y) >= mod)
		x -= mod;
}
inline void mod_dec(int &x, int y)
{
	if((x -= y) < 0)
		x += mod;
}
void pfs(int u)
{
	int sz = e[u].size();
	for(int i = 0; i < sz; ++i)
	{
		int v = e[u][i];
		e[v].erase(remove(e[v].begin(), e[v].end(), u), e[v].end());
		pfs(v);
	}
	memset(f[u] + 1, 0, mx * sizeof(int));
	if(sz > 0)
	{
		{ // pre
			int p, v = e[u][0];
			for(int i = l[u]; i <= r[u]; ++i)
				pre[v][i] = 1;
			for(int i = 1; i < sz; ++i)
			{
				p = v, v = e[u][i];
				for(int j = l[u]; j <= r[u]; ++j)
					pre[v][j] = (LL)pre[p][j] * h[p][j] % mod;
			}
		}
		{ // suf
			int p, v = e[u][sz - 1];
			for(int i = l[u]; i <= r[u]; ++i)
				suf[v][i] = 1;
			for(int i = sz - 2; i >= 0; --i)
			{
				p = v, v = e[u][i];
				for(int j = l[u]; j <= r[u]; ++j)
					suf[v][j] = (LL)suf[p][j] * h[p][j] % mod;
			}
		}
		for(int i = l[u]; i <= r[u]; ++i)
			f[u][i] = (LL)suf[e[u][0]][i] * h[e[u][0]][i] % mod;
	}
	else
		for(int i = l[u]; i <= r[u]; ++i)
			f[u][i] = 1;
	memcpy(g[u] + 1, f[u] + 1, mx * sizeof(int));
	for(int i = 1; i <= mx; ++i)
		for(int j = i + i; j <= mx; j += i)
			mod_inc(g[u][i], g[u][j]);
	memset(h[u] + 1, 0, mx * sizeof(int));
	for(int i = 1; i <= mx; ++i)
		if(mu[i] > 0)
			for(int j = i; j <= mx; j += i)
				mod_inc(h[u][j], g[u][i]);
		else if(mu[i] < 0)
			for(int j = i; j <= mx; j += i)
				mod_dec(h[u][j], g[u][i]);
}
void dfs(int u)
{
	for(int i = l[u]; i <= r[u]; ++i)
		f[u][i] = (LL)f[u][i] * h[u][i] % mod;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it;
		memset(g[u] + 1, 0, mx * sizeof(int));
		for(int i = l[u]; i <= r[u]; ++i)
			g[u][i] = (LL)pre[v][i] * suf[v][i] % mod * h[u][i] % mod;
		for(int i = 1; i <= mx; ++i)
			for(int j = i + i; j <= mx; j += i)
				mod_inc(g[u][i], g[u][j]);
		memset(h[v] + 1, 0, mx * sizeof(int));
		for(int i = 1; i <= mx; ++i)
			if(mu[i] > 0)
				for(int j = i; j <= mx; j += i)
					mod_inc(h[v][j], g[u][i]);
			else if(mu[i] < 0)
				for(int j = i; j <= mx; j += i)
					mod_dec(h[v][j], g[u][i]);
		dfs(v);
	}
}
int main()
{
	mu[1] = 1;
	for(int i = 1; i < maxm; ++i)
		for(int j = i + i; j < maxm; j += i)
			mu[j] -= mu[i];
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", l + i);
		mx = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", r + i);
			if(mx < r[i])
				mx = r[i];
		}
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
		for(int i = 1, u, v; i < n; ++i)
		{
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		pfs(1);
		for(int i = l[1]; i <= r[1]; ++i)
			h[1][i] = 1;
		dfs(1);
		for(int i = 1; i <= n; ++i)
		{
			int ans = 0;
			for(int j = l[i]; j <= r[i]; ++j)
				ans = (ans + (LL)j * f[i][j]) % mod;
			printf("%d%c", ans, " \n"[i == n]);
		}
	}
	return 0;
}
