#include <cmath>
#include <cstdio>
const int maxn = 201;
int n, x[maxn], y[maxn], fa[maxn], L, R, M;
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
bool check()
{
	for(int i = 0; i < n; ++i)
		fa[i] = i;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			if((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) <= M)
				fa[find(j)] = find(i);
	return find(0) == find(1);
}
int main()
{
	for(int Case = 1; scanf("%d", &n) != EOF && n; ++Case)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d", x + i, y + i);
		L = 0, R = 2e6;
		while(L < R)
		{
			M = L + R >> 1;
			if(check())
				R = M;
			else
				L = M + 1;
		}
		if(Case > 1)
			puts("");
		printf("Scenario #%d\nFrog Distance = %.3f\n", Case, sqrt(L));
	}
	return 0;
}