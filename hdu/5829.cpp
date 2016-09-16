#include <cstdio>
#include <algorithm>
#include <functional>
typedef long long LL;
const int maxn = 100001, maxlen = 18, maxm = 1 << maxlen, mod = 998244353, gen = 3;
int pw[maxn], fact[maxn], iact[maxn];
int t, n, a[maxn], h[maxn];
int w[maxm], inv2[maxlen + 1], bitrev[maxm], f[maxm], g[maxm];
inline int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
inline int mod_add(int x, int y)
{
	return x + y >= mod ? x + y - mod : x + y;
}
inline int mod_sub(int x, int y)
{
	return x - y < 0 ? x - y + mod : x - y;
}
inline void NTT(int len, int x[], int flag)
{
	for(int i = 1; i < len; ++i)
		if(i < bitrev[i])
			std::swap(x[i], x[bitrev[i]]);
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d << 1)
			for(int k = 0; k < d; ++k)
			{
				int t = (LL)w[(maxm >> i) * k] * x[j + k + d] % mod;
				x[j + d + k] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag == -1)
	{
		std::reverse(x + 1, x + len);
		int bitLen;
		for(bitLen = 0; 1 << bitLen < len; ++bitLen);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * inv2[bitLen] % mod;
	}
}
template<class T> inline void scan(T &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
template<class T> inline void print(T x, char endc = '\n')
{
	int len = 0, num[20];
	while(x)
	{
		num[len++] = x % 10;
		x /= 10;
	}
	if(!len)
		num[len++] = 0;
	while(len)
		putchar('0' + num[--len]);
	putchar(endc);
}
int main()
{
	w[0] = 1;
	w[1] = mod_pow(gen, (mod - 1) >> maxlen); // make sure that mod = 2 ^ maxlen * k + 1
	for(int i = 2; i < maxm; ++i)
		w[i] = (LL)w[i - 1] * w[1] % mod;
	inv2[0] = 1;
	inv2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= maxlen; ++i)
		inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	pw[0] = fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		if((pw[i] = pw[i - 1] << 1) >= mod)
			pw[i] -= mod;
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	scan(t);
	while(t--)
	{
		scan(n);
		for(int i = 0; i < n; ++i)
			scan(a[i]);
		std::sort(a, a + n, std::greater<int>());
		int bitlen, len;
		for(bitlen = 0, len = 1; len < n << 1; ++bitlen, len <<= 1);
		for(int i = 1; i < len; ++i)
			bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (bitlen - 1));
		for(int i = 0; i < len; ++i)
			f[i] = i < n ? (LL)a[i] * pw[n - i - 1] % mod * fact[i] % mod : 0;
		NTT(len, f, 1);
		for(int i = 0; i < len; ++i)
			g[i] = i <= n ? iact[n - i] : 0;
		NTT(len, g, 1);
		for(int i = 0; i < len; ++i)
			f[i] = (LL)f[i] * g[i] % mod;
		NTT(len, f, -1);
		for(int i = 0; i < n; ++i)
		{
			h[i] = ((i ? h[i - 1] : 0) + (LL)f[n + i] * iact[i]) % mod;
			print(h[i], ' ');
		}
		putchar('\n');
	}
	return 0;
}
