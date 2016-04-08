#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 100001;
const LL mod = 9223372034707292160;
int t, n, m, cnt[maxn], fa[maxn];
LL a[maxn], bit[maxn], ans;
LL inc(LL x, LL y)
{
	LL ret = x + (y - mod);
	if(ret < 0)
		ret += mod; 
	return ret;
}
LL dec(LL x, LL y)
{
	LL ret = x - y;
	if(ret < 0)
		ret += mod;
	return ret;
}
LL mul(LL x, LL y)
{
	LL ret = x * y - (long long)((long double)x * y / mod + 0.001) * mod;
	if(ret < 0)
		ret += mod;
	return ret;
	/*LL ret = 0;
	while(y)
	{
		if(y & 1)
			ret = inc(ret, x);
		x = inc(x, x);
		y >>= 1;
	}
	return ret;*/
}
void add(int x, LL v)
{
	for( ; x <= n; x += x & -x)
		bit[x] = inc(bit[x], v);
}
LL sum(int x)
{
	LL ret = 0;
	for( ; x > 0; x -= x & -x)
		ret = inc(ret, bit[x]);
	return ret;
}
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		ans = 0;
		memset(cnt, 0, sizeof cnt);
		memset(bit, 0, sizeof bit);
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%lld", a + i);
			fa[i] = i;
			add(i, a[i]);
		}
		printf("Case #%d:\n", Case);
		for(int i = 1, l, r; i <= m; ++i)
		{
			scanf("%d%d", &l, &r);
			ans = inc(ans, dec(sum(r), sum(l - 1)));
			for(int j = find(r); j >= l; j = find(j - 1))
			{
				LL tmp = mul(a[j], a[j]);
				add(j, dec(tmp, a[j]));
				a[j] = tmp;
				++cnt[j];
				if(cnt[j] >= 31)
					fa[j] = find(j - 1);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
