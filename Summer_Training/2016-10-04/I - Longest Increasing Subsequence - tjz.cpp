#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 6, maxm = 1001;
int n, L[maxn], R[maxn], idx[maxn], op[maxn], seq[maxn], f[maxn];
bool vis[maxn];
long long g[maxn][maxm], h[maxn][maxm], ans[maxn];
void dfs(int cur, int dep)
{
	if(cur > n)
	{
		int len = 1;
		for(int i = 1; i <= n; ++i)
		{
			f[i] = 1;
			for(int j = 0; j < i; ++j)
				if(seq[j] < seq[i] && f[i] < f[j] + 1)
					f[i] = f[j] + 1;
			if(len < f[i])
				len = f[i];
		}
		g[0][0] = h[0][0] = 1;
		for(int i = 1; i <= n; ++i)
		{
			int pid = idx[i - 1], cid = idx[i], diff = op[i];
			if(diff)
				for(int j = L[cid]; j <= R[cid]; ++j)
					g[i][j] = L[pid] < j ? h[i - 1][std::min(j - 1, R[pid])] : 0;
			else
				for(int j = L[cid]; j <= R[cid]; ++j)
					g[i][j] = L[pid] <= j && j <= R[pid] ? g[i - 1][j] : 0;
			for(int j = L[cid]; j <= R[cid]; ++j)
				h[i][j] = (j > L[cid] ? h[i][j - 1] : 0) + g[i][j];
		}
		ans[len] += h[n][R[idx[n]]];
		return;
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
		{
			vis[i] = 1;
			idx[cur] = i;
			op[cur] = 1;
			seq[i] = dep;
			dfs(cur + 1, dep + 1);
			if(cur > 1 && idx[cur - 1] < i)
			{
				op[cur] = 0;
				seq[i] = dep - 1;
				dfs(cur + 1, dep);
			}
			vis[i] = 0;
		}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", L + i, R + i);
	dfs(1, 1);
	for(int i = 1; i <= n; ++i)
		printf("%lld%c", ans[i], " \n"[i == n]);
	return 0;
}
