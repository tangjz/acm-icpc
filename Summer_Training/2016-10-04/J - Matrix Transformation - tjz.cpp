#include <stdio.h>
const int maxn = 202;
int n, q, L[maxn * maxn], R[maxn * maxn], U[maxn * maxn], D[maxn * maxn];
inline int idx(int x, int y)
{
	return x * (n + 2) + y;
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 0; i <= n + 1; ++i)
		for(int j = 0; j <= n + 1; ++j)
		{
			L[idx(i, j)] = j ? idx(i, j - 1) : 0;
			R[idx(i, j)] = j <= n ? idx(i, j + 1) : 0;
			U[idx(i, j)] = i ? idx(i - 1, j) : 0;
			D[idx(i, j)] = i <= n ? idx(i + 1, j) : 0;
		}
	while(q--)
	{
		int t, l, r, d;
		scanf("%d%d%d%d", &t, &l, &r, &d);
		if(!d)
			continue;
		++l, ++r;
		if(t == 1)
		{
			int pL = idx(l, 0), pR = idx(l, n + 1), x = pL;
			for(int i = 1; i <= d; ++i, x = R[x]);
			int y = R[x];
			for(int i = l; i <= r; ++i, pL = D[pL], pR = D[pR], x = D[x], y = D[y])
			{
				int s = R[pL], t = L[pR];
				R[pL] = y;
				L[y] = pL;
				R[x] = pR;
				L[pR] = x;
				L[s] = t;
				R[t] = s;
			}
			for(int i = 1, u = R[idx(l - 1, 0)], v = R[idx(l, 0)]; i <= n; ++i, u = R[u], v = R[v])
				U[v] = u, D[u] = v;
			for(int i = 1, u = R[idx(r, 0)], v = R[idx(r + 1, 0)]; i <= n; ++i, u = R[u], v = R[v])
				U[v] = u, D[u] = v;
		}
		else
		{
			int pU = idx(0, l), pD = idx(n + 1, l), x = pU;
			for(int i = 1; i <= d; ++i, x = D[x]);
			int y = D[x];
			for(int i = l; i <= r; ++i, pU = R[pU], pD = R[pD], x = R[x], y = R[y])
			{
				int s = D[pU], t = U[pD];
				D[pU] = y;
				U[y] = pU;
				D[x] = pD;
				U[pD] = x;
				U[s] = t;
				D[t] = s;
			}
			for(int i = 1, u = D[idx(0, l - 1)], v = D[idx(0, l)]; i <= n; ++i, u = D[u], v = D[v])
				L[v] = u, R[u] = v;
			for(int i = 1, u = D[idx(0, r)], v = D[idx(0, r + 1)]; i <= n; ++i, u = D[u], v = D[v])
				L[v] = u, R[u] = v;
		}
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1, u = idx(i, 0); j <= n; ++j)
		{
			u = R[u];
			int x = u / (n + 2) - 1, y = u % (n + 2) - 1;
			printf("%d%c", x * n + y, " \n"[j == n]);
		}
	return 0;
}
