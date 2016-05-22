#include <stdio.h>
typedef long long LL;
const int maxn = 61, mod = 1000000007;
int iact[maxn + 1], t, deg, val[maxn + 1], nxt[maxn + 1], seq[maxn + 1];
LL n, m;
inline int mod_add(int x, int y)
{
	return x + y < mod ? x + y : x + y - mod;
}
inline int mod_dec(int x, int y)
{
	return x - y >= 0 ? x - y : x - y + mod;
}
int value(int x)
{
	if(x < deg)
		return val[x];
	static int pre[maxn], suf[maxn];
	pre[0] = x;
	for(int i = 1; i < deg; ++i)
		pre[i] = (LL)(x - i) * pre[i - 1] % mod;
	suf[deg - 1] = x - deg + 1;
	for(int i = deg - 2; i >= 0; --i)
		suf[i] = (LL)(x - i) * suf[i + 1] % mod;
	int ret = 0;
	for(int i = 0; i < deg; ++i)
	{
		int tmp = (LL)val[i] * iact[i] % mod * iact[deg - 1 - i] % mod;
		if(i > 0)
			tmp = (LL)tmp * pre[i - 1] % mod;
		if(i < deg - 1)
			tmp = (LL)tmp * suf[i + 1] % mod;
		if(((deg - 1 - i) & 1) && tmp > 0)
			tmp = mod - tmp;
		ret += tmp;
		if(ret >= mod)
			ret -= mod;
	}
	return ret;
}
int mod_inv(int x)
{
	return x <= 1 ? x : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
struct Poly
{
	int deg, term[maxn << 1];
	Poly operator * (const Poly &t) const
	{
		Poly ret = {deg + t.deg - 1};
		for(int i = 0; i < deg; ++i)
			for(int j = 0; j < t.deg; ++j)
				ret.term[i + j] = (ret.term[i + j] + (LL)term[i] * t.term[j]) % mod;
		for( ; ret.deg > 0 && !ret.term[ret.deg - 1]; --ret.deg);
		return ret;
	}
	Poly operator % (const Poly &t) const
	{
		Poly ret = *this;
		for(int i = ret.deg; i >= t.deg; --i)
		{
			int coeff = (LL)ret.term[i - 1] * mod_inv(t.term[t.deg - 1]) % mod;
			for(int j = 1; j <= t.deg; ++j)
				if((ret.term[i - j] = (ret.term[i - j] - (LL)coeff * t.term[t.deg - j]) % mod) < 0)
					ret.term[i - j] += mod;
		}
		for( ; ret.deg > 0 && !ret.term[ret.deg - 1]; --ret.deg);
		return ret;
	}
} A, B, M;
int main()
{
	iact[0] = 0;
	iact[1] = 1;
		for(int i = 2; i <= maxn; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	iact[0] = 1;
	for(int i = 1; i <= maxn; ++i)
		iact[i] = iact[i - 1] * (LL)iact[i] % mod;
	scanf("%d", &t);
	while(t--)
	{
		int len;
		scanf("%lld%lld", &n, &m);
		{
			LL tmp = (n << 1) - 1;
			deg = val[0] = 1;
			for(len = 1; --tmp >= 0; ++len)
			{
				for(int i = 0, pos = tmp & 1; i <= deg; ++i, pos = mod_add(pos, 2))
					nxt[i] = mod_add(i > 0 ? nxt[i - 1] : 0, value(pos));
				++deg;
				for(int i = 0; i < deg; ++i)
					val[i] = nxt[i];
				tmp >>= 1;
				seq[len] = value(tmp % mod);
			}
			--len;
		}
		{
			LL tmp = n - 1;
			deg = val[0] = 1;
			for(int o = 1; --tmp >= 0; ++o)
			{
				for(int i = 0, pos = tmp & 1; i <= deg; ++i, pos = mod_add(pos, 2))
					nxt[i] = mod_add(i > 0 ? nxt[i - 1] : 0, value(pos));
				++deg;
				for(int i = 0; i < deg; ++i)
					val[i] = nxt[i];
				tmp >>= 1;
				seq[o] = mod_dec(seq[o], value(tmp % mod));
			}
		}
		//for(int i = 1; i <= len; ++i)
		//	printf("%d%c", seq[i], " \n"[i == len]);
		M = (Poly){len + 1};
		M.term[len] = 1;
		for(int i = 0; i < len; ++i)
			M.term[i] = mod - seq[len - i];
		A = (Poly){1, 1};
		B = (Poly){2, 0, 1};
		for(m += len - 1; m > 0; m >>= 1, B = B * B % M)
			if(m & 1)
				A = A * B % M;
		printf("%d\n", A.deg == len ? A.term[len - 1] : 0);
	}
	return 0;
}
