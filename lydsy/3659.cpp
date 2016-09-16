#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 101, maxm = 200001, mod = 1000003;
int fact[maxm], n, e[maxn][maxn], in[maxn], out[maxn], tot, tim[maxn], mat[maxn][maxn], ans;
inline int mod_inv(int x)
{
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
void dfs(int u)
{
	tim[u] = tot++;
	for(int v = 0; v < n; ++v)
		if(tim[v] == -1 && e[u][v])
			dfs(v);
}
int main()
{
	fact[0] = 1;
	for(int i = 1; i < maxm; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	while(scanf("%d", &n) == 1 && n)
	{
		memset(in, 0, n * sizeof(int));
		for(int i = 0; i < n; ++i)
		{
			memset(e[i], 0, n * sizeof(int));
			scanf("%d", out + i);
			for(int o = 0, j; o < out[i]; ++o)
			{
				scanf("%d", &j);
				--j;
				++e[i][j];
				++in[j];
			}
		}
		tot = 0;
		memset(tim, -1, n * sizeof(int));
		dfs(0);
		bool flag = 1;
		for(int i = 0; i < n; ++i)
			if(tim[i] == -1 && (in[i] || out[i])
			|| tim[i] != -1 && in[i] != out[i])
			{
				flag = 0;
				break;
			}
		if(!flag)
		{
			puts("0");
			continue;
		}
		ans = fact[out[0]];
		for(int i = 1; i < n; ++i)
		{
			if(tim[i] == -1)
				continue;
			ans = (LL)ans * fact[out[i] - 1] % mod;
			mat[tim[i]][tim[i]] = out[i] - e[i][i];
			for(int j = 1; j < n; ++j)
			{
				if(tim[j] == -1 || i == j)
					continue;
				mat[tim[i]][tim[j]] = e[i][j] ? mod - e[i][j] : 0;
			}
		}
		for(int i = 1; i < tot; ++i)
		{
			int k = -1;
			for(int j = i; j < tot; ++j)
				if(mat[j][i])
				{
					k = j;
					break;
				}
			if(k == -1)
			{
				ans = 0;
				break;
			}
			if(i != k)
			{
				for(int j = i; j < tot; ++j)
					std::swap(mat[i][j], mat[k][j]);
				ans = mod - ans;
			}
			ans = (LL)ans * mat[i][i] % mod;
			int inver = mod - mod_inv(mat[i][i]);
			for(int j = i + 1; j < tot; ++j)
			{
				int d = (LL)mat[j][i] * inver % mod;
				for(k = i; k < tot; ++k)
					mat[j][k] = (mat[j][k] + (LL)mat[i][k] * d) % mod;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
