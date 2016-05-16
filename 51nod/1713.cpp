#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 50, maxp = 9;
int n, m, s, g[maxn];
double f[1 << maxp][maxn], mat[maxn][maxn + 1];
bool e[maxn][maxn];
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u][v] = e[v][u] = 1;
	}
	for(int i = 0; i < maxp; ++i)
	{
		int u;
		scanf("%d", &u);
		g[u] |= 1 << i;
	}
	scanf("%d", &s);
	for(int msk = (1 << maxp) - 1; msk >= g[s]; --msk)
	{
		int cnt = 0, sum[3] = {};
		for(int i = 0; i < maxp; ++i)
			if(msk & (1 << i))
				if(++sum[i / 3] == 2)
					++cnt;
		if(cnt > 1)
			continue;
		memset(mat, 0, sizeof mat);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				if(!e[i][j])
					continue;
				mat[i][i] += 1;
				mat[i][n] += 1;
				if((msk | g[j]) == msk)
					mat[i][j] -= 1;
				else
					mat[i][n] += f[msk | g[j]][j];
			}
		for(int i = 0; i < n; ++i)
		{
			int k = i;
			for(int j = i + 1; j < n; ++j)
				if(fabs(mat[k][i]) < fabs(mat[j][i]))
					k = j;
			if(i < k)
				for(int j = i; j <= n; ++j)
					std::swap(mat[i][j], mat[k][j]);
			double t = mat[i][i];
			for(int j = i; j <= n; ++j)
				mat[i][j] /= t;
			for(int j = 0; j < n; ++j)
			{
				if(i == j)
					continue;
				t = mat[j][i];
				for(int k = i; k <= n; ++k)
					mat[j][k] -= mat[i][k] * t;
			}
		}
		for(int i = 0; i < n; ++i)
			f[msk][i] = mat[i][n];
	}
	printf("%.6f\n", f[g[s]][s]);
	return 0;
}
