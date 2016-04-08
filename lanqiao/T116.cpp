#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 51, maxm = 26, maxp = 11, INF = 0x3f3f3f3f;
int n, m, p, x[maxn + maxm], y[maxn + maxm], dis[maxm][maxn], ord[maxm], f[maxp][maxn], g[maxp], h[maxp];
double ans;
int counter;
void dfs(int dep)
{
	if(++counter > 850000)
		return;
	if(dep == p)
	{
		double tmp = 0;
		for(int i = 0; i < n; ++i)
			tmp += sqrt(f[dep][i]);
		if(ans > tmp)
		{
			ans = tmp;
			memcpy(h, g, p * sizeof(int));
		}
		return;
	}
	for(int i = dep ? g[dep - 1] + 1 : 0, j = m - p + dep; i <= j; ++i)
	{
		bool flag = 0;
		int o = ord[i];
		for(int k = 0; k < n; ++k)
		{
			if(f[dep][k] < dis[o][k])
				f[dep + 1][k] = f[dep][k];
			else
			{
				f[dep + 1][k] = dis[o][k];
				flag = 1;
			}
		}
		if(!flag)
			continue;
		g[dep] = i;
		dfs(dep + 1);
	}
}
void pfs(int dep)
{
	if(++counter > 850000)
		return;
	if(dep == p)
	{
		double tmp = 0;
		for(int i = 0; i < n; ++i)
			tmp += sqrt(f[dep][i]);
		if(ans > tmp)
		{
			ans = tmp;
			memcpy(h, g, p * sizeof(int));
		}
		return;
	}
	for(int j = dep ? g[dep - 1] + 1 : 0, i = m - p + dep; j <= i; --i)
	{
		bool flag = 0;
		int o = ord[i];
		for(int k = 0; k < n; ++k)
		{
			if(f[dep][k] < dis[o][k])
				f[dep + 1][k] = f[dep][k];
			else
			{
				f[dep + 1][k] = dis[o][k];
				flag = 1;
			}
		}
		if(!flag)
			continue;
		g[dep] = i;
		pfs(dep + 1);
	}
}
inline int sqr(int x)
{
	return x * x;
}
int main()
{
	srand(time(NULL));
	scanf("%d%d%d", &n, &m, &p);
	for(int i = 0; i < n + m; ++i)
		scanf("%d%d", x + i, y + i);
	for(int i = 0; i < m; ++i)
	{
		ord[i] = i;
		for(int j = 0; j < n; ++j)
			dis[i][j] = sqr(x[n + i] - x[j]) + sqr(y[n + i] - y[j]);
	}
	random_shuffle(ord, ord + m);
	ans = 1e10;
	memset(f[0], 0x3f, n * sizeof(int));
	dfs(0);
	pfs(0);
	for(int i = 0; i < p; ++i)
		h[i] = ord[h[i]];
	sort(h, h + p);
	for(int i = 0; i < p; ++i)
		printf("%d%c", h[i] + 1, " \n"[i == p - 1]);
	return 0;
}
