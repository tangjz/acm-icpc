#include <cmath>
#include <cstdio>
#include <cstring>
typedef unsigned int UL;
const int maxp = 131, maxq = 2000001, maxs = 1 << 14, maxd = 1415;
UL tot, prime[maxp], cnt[maxp];
UL C(UL x, UL y)
{
	UL ret = 1;
	memset(cnt, 0, tot * sizeof(UL));
	for(UL i = 0; i < y; ++i)
	{
		{
			UL val = x - i;
			for(UL j = 0; j < tot; ++j)
				for( ; val % prime[j] == 0; ++cnt[j], val /= prime[j]);
			ret *= val;
		}
		{
			UL val = i + 1;
			for(UL j = 0; j < tot; ++j)
				for( ; val % prime[j] == 0; --cnt[j], val /= prime[j]);
			//ret *= mod_inv(val);
		}
	}
	for(UL i = 0; i < tot; ++i)
		for( ; cnt[i]--; ret *= prime[i]);
	return ret;
}
struct Matrix
{
	UL r, c, num[maxp][maxp];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {r, t.c};
		for(UL i = 0; i < r; ++i)
			for(UL j = 0; j < c; ++j)
				for(UL k = 0; k < t.c; ++k)
					ret.num[i][k] += num[i][j] * t.num[j][k];
		return ret;
	}
} g[maxd];
UL n, p, q, sz, f[maxs][maxp], ans;
int main()
{
	scanf("%u%u%u", &n, &p, &q);
	if(p >= n)
		p = n - 1;
	sz = 1;
	for(UL tmp = sqrt((p ? p : 1) * q); sz < tmp; sz <<= 1);
	for(UL i = 2; i <= p; ++i)
	{
		if(!cnt[i])
			prime[tot++] = i;
		for(UL j = 0; j < tot && i * prime[j] <= p; ++j)
		{
			cnt[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	g[1].r = g[1].c = p + 1;
	for(UL i = 0; i <= p; ++i)
		for(UL j = i; j <= p; ++j)
			g[1].num[i][j] = C(n - p + j, j - i);
	for(UL i = 0; i <= p; ++i)
		f[0][i] = 1;
	for(UL i = 1; i < sz; ++i)
		for(UL j = 0; j <= p; ++j)
			for(UL k = j; k <= p; ++k)
				f[i][k] += f[i - 1][j] * g[1].num[j][k];
	g[0].r = g[0].c = p + 1;
	for(UL i = 0; i <= p; ++i)
		g[0].num[i][i] = 1;
	for(UL i = 1; i < sz; i <<= 1)
		g[1] = g[1] * g[1];
	for(UL i = 2; i * sz <= q; ++i)
		g[i] = g[i - 1] * g[1];
	for(UL i = 1, x = sz == 1, y = sz > 1; i <= q; ++i, y == sz - 1 ? ++x, y = 0 : ++y)
	{
		UL tmp = 0;
		for(UL j = 0; j <= p; ++j)
			tmp += f[y][j] * g[x].num[j][p];
		ans ^= i * tmp;
	}
	printf("%u\n", ans);
	return 0;
}
