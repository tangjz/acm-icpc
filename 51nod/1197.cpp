#include <stdio.h>
typedef long long LL;
const int maxn = 61, mod = 1000000007;
int iact[maxn + 1], deg, val[maxn + 1], nxt[maxn + 1], seq[maxn + 1];
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
struct Matrix
{
	int r, c, num[maxn][maxn];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {r, t.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = (ret.num[i][k] + (LL)num[i][j] * t.num[j][k]) % mod;
		return ret;
	}
	Matrix pow(LL k)
	{
		Matrix ret = {r, r}, tmp = *this;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		for( ; k > 0; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
} A;
int main()
{
	iact[0] = 0;
	iact[1] = 1;
		for(int i = 2; i <= maxn; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	iact[0] = 1;
	for(int i = 1; i <= maxn; ++i)
		iact[i] = iact[i - 1] * (LL)iact[i] % mod;
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
		A = (Matrix){len, len};
		for(int i = 1; i < len; ++i)
			A.num[i][i - 1] = 1;
		for(int i = 0; i < len; ++i)
			A.num[i][len - 1] = seq[len - i];
		A = A.pow(m);
		printf("%d\n", A.num[len - 1][len - 1]);
	}
	return 0;
}
