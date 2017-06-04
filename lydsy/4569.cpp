#include <stdio.h>
#include <cstring>
const int maxn = 100001, maxd = 17, mod = 1000000007;
int n, m, tot, Log[maxn], lnk[maxd], dsu[maxn], tmp[maxn];
struct Limit {
	int nxt, x, y;
} e[maxn << 1 | 1];
int dsu_find(int x)
{
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v)
{
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] < dsu[v])
		dsu[v] = u;
	else if(dsu[u] > dsu[v])
		dsu[u] = v;
	else
	{
		--dsu[u];
		dsu[v] = u;
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 2; i <= n; ++i)
		Log[i] = Log[i >> 1] + 1;
	memset(lnk, -1, (Log[n] + 1) * sizeof(int));
	while(m--)
	{
		int L1, R1, L2, R2;
		scanf("%d%d%d%d", &L1, &R1, &L2, &R2);
		if(L1 == L2)
			continue;
		int d = Log[R1 - L1 + 1];
		e[tot] = (Limit){lnk[d], L1, L2};
		lnk[d] = tot++;
		if((1 << d) < R1 - L1 + 1)
		{
			e[tot] = (Limit){lnk[d], R1 - (1 << d) + 1, R2 - (1 << d) + 1};
			lnk[d] = tot++;
		}
	}
	memset(dsu + 1, -1, n * sizeof(int));
	for(int d = Log[n]; d >= 0; --d)
	{
		for(int it = lnk[d]; it != -1; it = e[it].nxt)
			dsu_merge(e[it].x, e[it].y);
		if(d > 0)
		{
			for(int i = 1; i <= n - (1 << d) + 1; ++i)
				tmp[i] = dsu_find(i);
			for(int i = 1; i <= n - (1 << d) + 1; ++i)
				if(tmp[i] != i)
					dsu_merge(i + (1 << (d - 1)), tmp[i] + (1 << (d - 1)));
		}
	}
	int ans = 300000003; // 9 / 10
	for(int i = 1; i <= n; ++i)
		if(i == dsu_find(i))
			ans = 10LL * ans % mod;
	printf("%d\n", ans);
	return 0;
}
