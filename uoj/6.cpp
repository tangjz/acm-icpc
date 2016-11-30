#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 5000, maxm = maxn * maxn;
int n, m, all, perm[maxm], ord[maxm], L[maxn], R[maxn], sz, out[maxn << 1];
inline int idx(int x, int y)
{
	return x * m + y;
}
inline void rdx(int o, int &x, int &y)
{
	x = o / m;
	y = o % m;
}
int main()
{
	// generation
	int xi, a, b, c, d, q;
	scanf("%d%d%d%d%d%d%d%d", &xi, &a, &b, &c, &d, &n, &m, &q);
	all = n * m;
	for(int i = 0; i < all; ++i)
		perm[i] = i;
	for(int i = 0; i < all; ++i)
	{
		xi = (((LL)a * xi + b) % d * xi + c) % d;
		std::swap(perm[i], perm[xi % (i + 1)]);
	}
	while(q--)
	{
		scanf("%d%d", &a, &b);
		std::swap(perm[--a], perm[--b]);
	}
	for(int i = 0; i < all; ++i)
		ord[perm[i]] = i;
	// greedy
	for(int i = 0; i < n; ++i)
	{
		L[i] = 0;
		R[i] = m - 1;
	}
	for(int i = 0; i < all; ++i)
	{
		int id = ord[i], x, y;
		rdx(id, x, y);
		if(y < L[x] || y > R[x])
			continue;
		out[sz++] = i + 1;
		for(int j = 0; j < x; ++j)
			if(R[j] > y)
				R[j] = y;
		for(int j = x + 1; j < n; ++j)
			if(L[j] < y)
				L[j] = y;
	}
	for(int i = 0; i < sz; ++i)
		printf("%d%c", out[i], " \n"[i == sz - 1]);
	return 0;
}
