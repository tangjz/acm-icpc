#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001;
int n, x[maxn], y[maxn], dsu[maxn], ordx[maxn], ordy[maxn];
int dsu_find(int x)
{
	return dsu[x] < 0 ? x : dsu[x] = dsu_find(dsu[x]);
}
void dsu_merge(int u, int v)
{
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] > dsu[v])
		std::swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[u];
	dsu[v] = u;
}
bool check(int lim)
{
	memset(dsu, -1, n * sizeof(int));
	{ // merge by x
		int low, upp;
		for(low = n - 1; low >= 0 && x[ordx[n - 1]] - x[ordx[low]] < lim; --low);
		for(upp = 0; upp < n && x[ordx[upp]] - x[ordx[0]] < lim; ++upp);
		if(upp - low - 1 <= 0)
			return 1;
		for(int i = 0; i <= low; ++i)
			dsu_merge(ordx[i], ordx[n - 1]);
		for(int i = upp; i < n; ++i)
			dsu_merge(ordx[0], ordx[i]);
	}
	{ // merge by y
		int low, upp;
		for(low = n - 1; low >= 0 && y[ordy[n - 1]] - y[ordy[low]] < lim; --low);
		for(upp = 0; upp < n && y[ordy[upp]] - y[ordy[0]] < lim; ++upp);
		if(upp - low - 1 <= 0)
			return 1;
		for(int i = 0; i <= low; ++i)
			dsu_merge(ordy[i], ordy[n - 1]);
		for(int i = upp; i < n; ++i)
			dsu_merge(ordy[0], ordy[i]);
	}
	for(int i = 1; i < n; ++i)
		if(dsu_find(0) != dsu_find(i))
			return 0;
	return 1;
}
bool cmpx(int const &i, int const &j)
{
	return x[i] < x[j];
}
bool cmpy(int const &i, int const &j)
{
	return y[i] < y[j];
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		x[i] = u + v;
		y[i] = u - v;
		ordx[i] = ordy[i] = i;
	}
	std::sort(ordx, ordx + n, cmpx);
	std::sort(ordy, ordy + n, cmpy);
	int L = 0, R = (int)2e9 + 1;
	while(L < R)
	{
		int M = R - ((R - L) >> 1);
		if(check(M))
			L = M;
		else
			R = M - 1;
	}
	printf("%d\n", L);
	return 0;
}
