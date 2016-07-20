#include <cstdio>
const int maxm = 101, maxk = 303;
int t, n, m, k, d[maxm], x[maxk], y[maxk], fa[maxk];
double p[maxm], ans;
int abs(int x)
{
	return x < 0 ? -x : x;
}
int dis(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
bool check(int D)
{
	for(int i = 0; i < k + 2; ++i)
		fa[i] = i;
	for(int i = 0; i < k; ++i)
	{
		if(x[i] + D >= n - 1 || y[i] - D <= 0)
			fa[find(i)] = find(k);
		if(x[i] - D <= 0 || y[i] + D >= n - 1)
			fa[find(i)] = find(k + 1);
	}
	for(int i = 0; i < k; ++i)
		for(int j = i + 1; j < k; ++j)
			if(dis(x[i], y[i], x[j], y[j]) <= D + D)
				fa[find(i)] = find(j);
	return find(k) != find(k + 1);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++i)
			scanf("%d%lf", d + i, p + i);
		for(k = 0; scanf("%d", x + k) != EOF && x[k] != -1; ++k)
			scanf("%d", y + k);
		int L = 0, R = n, M;
		while(L < R)
		{
			M = L + R + 1 >> 1;
			if(check(M))
				L = M;
			else
				R = M - 1;
		}
		ans = 0;
		for(int i = 0; i < m; ++i)
			if(d[i] <= L)
				ans += p[i];
		printf("%f\n", ans);
	}
	return 0;
}
