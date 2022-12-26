#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 51, INF = 0x3f3f3f3f;
int n, e[2][maxn][maxn], match[2][maxn], work[2][maxn], tim[2][maxn], total;
int (*cur_e)[maxn], *cur_match, lx[maxn], ly[maxn];
bool sx[maxn], sy[maxn];
bool path(int u)
{
	sx[u] = 1;
	for(int v = 1; v <= n; ++v)
	{
		if(sy[v] || lx[u] + ly[v] != cur_e[u][v])
			continue;
		sy[v] = 1;
		if(!cur_match[v] || path(cur_match[v]))
		{
			cur_match[v] = u;
			return 1;
		}
	}
	return 0;
}
void KM()
{
	for(int i = 1; i <= n; ++i)
	{
		lx[i] = INF;
		for(int j = 1; j <= n; ++j)
			lx[i] = std::min(lx[i], cur_e[i][j]);
	}
	memset(ly + 1, 0, n * sizeof(int));
	for(int i = 1; i <= n; ++i)
		while(1)
		{
			memset(sx + 1, 0, n * sizeof(bool));
			memset(sy + 1, 0, n * sizeof(bool));
			if(path(i))
				break;
			int delta = INF;
			for(int j = 1; j <= n; ++j)
			{
				if(!sx[j])
					continue;
				for(int k = 1; k <= n; ++k)
					if(!sy[k])
						delta = std::min(delta, cur_e[j][k] - lx[j] - ly[k]);
			}
			for(int j = 1; j <= n; ++j)
			{
				if(sx[j])
					lx[j] += delta;
				if(sy[j])
					ly[j] -= delta;
			}
		}
}
int main()
{
	for(int Case = 1; scanf("%d", &n) == 1 && n; ++Case)
	{
		for(int o = 0; o < 2; ++o)
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
					scanf("%d", e[o][i] + j);
		cur_e = e[0];
		cur_match = match[0];
		memset(match[0] + 1, 0, n * sizeof(int));
		KM();
		for(int i = 1; i <= n; ++i)
		{
			int j = cur_match[i];
			work[0][j] = i;
			tim[0][j] = cur_e[j][i];
		}
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				cur_e[i][j] = e[1][i][j] + std::max(tim[0][i], tim[0][cur_match[j]]);
		cur_match = match[1];
		memset(match[1] + 1, 0, n * sizeof(int));
		KM();
		total = 0;
		for(int i = 1; i <= n; ++i)
		{
			int j = cur_match[i];
			work[1][j] = i;
			tim[1][j] = cur_e[j][i];
			total += tim[1][j] - tim[0][j] - e[1][j][i];
		}
		printf("Case %d:\n", Case);
		for(int i = 1; i <= n; ++i)
			printf("Worker %d: %d %d %d\n", i, work[0][i], work[1][i], tim[1][i]);
		printf("Total idle time: %d\n", total);
	}
	return 0;
}
