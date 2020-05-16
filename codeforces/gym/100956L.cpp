#include <cmath>
#include <cstdio>
#include <cstring>
typedef long long LL;
typedef unsigned long long ULL;
typedef long double DB;
const int maxm = 100001, maxs = ((maxm - 1) >> 6) + 1, maxd = 1 << 16;
int t, n, m, fsz, gsz, pos[maxd | 1];
ULL f[maxs], g[maxs];
DB ans;
int lowbit(ULL a[], int sz, int low)
{
	int sta = low >> 6, rem = low & 63;
	for(int i = sta; i < sz; ++i)
	{
		ULL mask = a[i];
		if(i == sta && rem)
			mask = (mask >> rem) << rem;
		if(!mask)
			continue;
		int dt = 0;
		if(!(mask & ((1ULL << 32) - 1)))
		{
			mask >>= 32;
			dt += 32;
		}
		if(!(mask & ((1 << 16) - 1)))
		{
			mask >>= 16;
			dt += 16;
		}
		return i << 6 | (dt + pos[mask & ((1 << 16) - 1)]);
	}
	return sz << 6;
}
int main()
{
	for(int i = 1; i < maxd; ++i)
		pos[i] = i & 1 ? 0 : pos[i >> 1] + 1;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		fsz = (m >> 6) + 1;
		memset(f, 0, fsz * sizeof(ULL));
		while(n--)
		{
			int x;
			scanf("%d", &x);
			f[x >> 6] |= 1ULL << (x & 63);
		}
		ans = 1e20;
		for(int dt = 1, lbt = -1; dt < m; ++dt)
		{
			if(lbt <= dt)
				lbt = lowbit(f, fsz, dt + 1);
			if(m - dt <= lbt)
				break;
			gsz = ((m - dt) >> 6) + 1;
			int dx = dt >> 6, dy = dt & 63;
			for(int i = (lbt + 1) >> 6; i < gsz; ++i)
			{
				g[i] = i + dx < fsz ? (f[i + dx] >> dy) : 0;
				if(dy && i + dx + 1 < fsz)
					g[i] |= f[i + dx + 1] << (64 - dy);
				g[i] &= f[i];
			}
			int lbt2 = lowbit(g, gsz, lbt + 1);
			if(lbt2 <= m - dt)
			{
				int a = lbt, b = lbt2, c = b + dt;
				DB area = sqrt((LL)(a + b - c) * (a + c - b) * (b + c - a) / 16.0 * (a + b + c));
				if(area < ans)
					ans = area;
			}
		}
		if(ans < 1e19)
			printf("%.15f\n", (double)ans);
		else
			puts("-1");
	}
	return 0;
}