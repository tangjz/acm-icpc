#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
typedef long double DB;
const int maxn = 5001, maxd = 19, maxp = 1000001;
int tot, pr[maxp], d[maxp];
int n, m, q, sz, lim[maxd], cnt[maxd];
LL a[maxn], b[maxn], mod, p[maxd];
void exgcd(LL a, LL b, LL &x, LL &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
inline LL mod_inv(LL x, LL p)
{
	LL u, v;
	exgcd(x, p, u, v);
	return u < 0 ? u + p : u;
}
inline LL mod_mul(LL x, LL y, LL p)
{
	LL ret = x * y - (LL)((DB)x * y / p + 0.01) * p;
	return ret < 0 ? ret + p : ret;
}
int main()
{
	for(int i = 2; i < maxp; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxp; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%I64d", a + i);
	for(int i = 0; i < m; ++i)
		scanf("%I64d", b + i);
	scanf("%d", &q);
	while(q--)
	{
		scanf("%I64d", &mod);
		sz = 0;
		LL tmp = mod;
		for(int i = 0; i < tot; ++i)
		{
			if(tmp % pr[i])
				continue;
			for(tmp /= pr[i], lim[sz] = 1; tmp % pr[i] == 0; tmp /= pr[i], ++lim[sz]);
			p[sz++] = pr[i];
		}
		if(tmp > 1)
			for(int i = 0; i < n; ++i)
			{
				LL r = std::__gcd(a[i], tmp);
				if(r > 1 && r < tmp)
				{
					for(tmp /= r, lim[sz] = 1; tmp % r == 0; tmp /= r, ++lim[sz]);
					p[sz++] = r;
					break;
				}
			}
		if(tmp > 1)
			for(int i = 0; i < m; ++i)
			{
				LL r = std::__gcd(b[i], tmp);
				if(r > 1 && r < tmp)
				{
					for(tmp /= r, lim[sz] = 1; tmp % r == 0; tmp /= r, ++lim[sz]);
					p[sz++] = r;
					break;
				}
			}
		if(tmp > 1) // may not prime, but combined effect with numerator and denominator
		{
			lim[sz] = 1;
			p[sz++] = tmp;
		}
		memset(cnt, 0, sz * sizeof(int));
		LL fz = 1, fm = 1;
		for(int i = 0; i < n; ++i)
		{
			tmp = a[i];
			for(int j = 0; j < sz; ++j)
				for( ; tmp % p[j] == 0; tmp /= p[j], ++cnt[j]);
			fz = mod_mul(fz, tmp, mod);
		}
		for(int i = 0; i < m; ++i)
		{
			tmp = b[i];
			for(int j = 0; j < sz; ++j)
				for( ; tmp % p[j] == 0; tmp /= p[j], --cnt[j]);
			fm = mod_mul(fm, tmp, mod);
		}
		bool flag = 1;
		for(int i = 0; i < sz && flag; ++i)
			flag &= cnt[i] >= 0;
		if(!flag)
		{
			puts("DIVISION BY ZERO");
			continue;
		}
		for(int i = 0; i < sz; ++i)
			for( ; cnt[i]--; fz = mod_mul(fz, p[i], mod));
		fz = mod_mul(fz, mod_inv(fm, mod), mod);
		printf("%I64d\n", fz);
	}
	return 0;
}
