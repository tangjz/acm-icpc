#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
typedef unsigned int UL;
typedef unsigned long long ULL;
const int maxn = 15, maxm = 100001, maxs = ((maxm - 1) >> 6) + 1, maxp = 1 << 16 | 1;
template<class T> inline int sgn(T x)
{
	return (x > 0) - (x < 0);
}
struct Point
{
	int x, y, z;
	void read()
	{
		scanf("%d%d%d", &x, &y, &z);
	}
	int dot(const Point &t) const
	{
		return x * t.x + y * t.y + z * t.z;
	}
	int mode() const
	{
		return dot(*this);
	}
	LL dotLL(const Point &t) const
	{
		return (LL)x * t.x + (LL)y * t.y + (LL)z * t.z;
	}
	LL modeLL() const
	{
		return dotLL(*this);
	}
	Point det(const Point &t) const
	{
		return (Point){y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x};
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y, z - t.z};
	}
} ant[maxn], bar[maxm];
int t, n, m, a[maxn], r[maxm], ans[maxm + 2];
int g[1 << maxn | 1], h[1 << maxn | 1], sz, lbt[maxp], cnt[maxp];
inline int popcount(UL x)
{
	return cnt[x >> 16] + cnt[x & 65535];
}
inline int popcount(ULL x)
{
	return popcount((UL)(x >> 32)) + popcount((UL)x);
}
struct Bitset
{
	ULL data[maxs];
	void reset()
	{
		memset(data, 0, sz * sizeof(ULL));
	}
	void set(int x)
	{
		data[x >> 6] |= 1ULL << (x & 63);
	}
	void operator = (Bitset const &src)
	{
		memcpy(data, src.data, sz * sizeof(ULL));
	}
	void operator |= (Bitset const &src)
	{
		register int i;
		for(i = 0; i < sz; ++i)
			data[i] |= src.data[i];
	}
	int popcount() const
	{
		register int ret = 0, i;
		for(i = 0; i < sz; ++i)
			ret += ::popcount(data[i]);
		return ret;
	}
} f[maxn], tmp[maxn + 2];
void dfs(int dep, int mask)
{
	if(dep == n)
	{
		g[mask] = mask ? tmp[dep].popcount() : 0;
		return;
	}
	tmp[dep + 1] = tmp[dep];
	dfs(dep + 1, mask);
	tmp[dep + 1] |= f[dep];
	dfs(dep + 1, mask | 1 << dep);
}
int main()
{
	register int i, j, all;
	register ULL res;
	for(i = 1; i < maxp; ++i)
	{
		lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
		cnt[i] = cnt[i >> 1] + (i & 1);
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		all = 1 << n;
		sz = ((m - 1) >> 6) + 1;
		for(i = 0; i < n; ++i)
		{
			ant[i].read();
			scanf("%d", a + i);
		}
		for(i = 0; i < m; ++i)
		{
			bar[i].read();
			scanf("%d", r + i);
		}
		for(i = 0; i < n; ++i)
			for(j = 0, f[i].reset(); j < m; ++j)
				if(sgn((ant[i] - bar[j]).mode() - r[j] * r[j]) < 0
				|| sgn(bar[j].mode() - r[j] * r[j]) < 0
				|| (ant[i].det(bar[j]).modeLL() < r[j] * r[j] * (LL)ant[i].mode()
				&& ant[i].dot(ant[i] - bar[j]) > 0 && ant[i].dot(bar[j]) > 0))
					f[i].set(j);
		tmp[0].reset();
		dfs(0, 0);
		memset(ans, 0, (m + 1) * sizeof(int));
		for(i = 1, h[0] = 0; i < all; ++i)
		{
			h[i] = h[i ^ (1 << lbt[i])] + a[lbt[i]];
			if(ans[g[i]] < h[i])
				ans[g[i]] = h[i];
		}
		res = ans[0];
		for(i = 1; i <= m; ++i)
		{
			if(ans[0] < ans[i])
				ans[0] = ans[i];
			res += (i + 1ULL) * ans[0];
		}
		printf("%llu\n", res);
	}
	return 0;
}
