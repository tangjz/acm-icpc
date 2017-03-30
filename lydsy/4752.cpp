// don't copy this code, thanks!
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
typedef double DB;
const int maxn = 501, maxLen = 10, maxm = 1 << maxLen | 1;
const LL maxv = (LL)1e13;
const DB pi = acos(-1);
struct complex {
	DB r, i;
	complex() {}
	complex(DB r, DB i) : r(r), i(i) {}
	complex operator + (complex const &t) const {
		return complex(r + t.r, i + t.i);
	}
	complex operator - (complex const &t) const {
		return complex(r - t.r, i - t.i);
	}
	complex operator * (complex const &t) const {
		return complex(r * t.r - i * t.i, r * t.i + i * t.r);
	}
	complex conj() const {
		return complex(r, -i);
	}
	complex sqr() const {
		return (*this) * (*this);
	}
} w[maxm];
inline complex getRoot(int id, int ex, int flag)
{
	complex ret = w[id << (maxLen - ex)];
	return flag < 0 ? ret.conj() : ret;
}
void FFT(int n, complex a[], int flag)
{
	for(int i = 1, j = n >> 1, k; i < n - 1; ++i)
	{
		if(i < j)
			std::swap(a[i], a[j]);
		for(k = n >> 1; j >= k; j -= k, k >>= 1);
		j += k;
	}
	for(int i = 1, d = 1; d < n; ++i, d <<= 1)
		for(int j = 0; j < n; j += d << 1)
			for(int k = 0; k < d; ++k)
			{
				complex *A = a + j, t = getRoot(k, i, flag) * A[d + k];
				A[d + k] = A[k] - t;
				A[k] = A[k] + t;
			}
	if(flag == -1)
		for(int i = 0; i < n; ++i)
			a[i].r /= n;
}
int n, mod, nlim, sp, msk, sd, fact[maxn], inv[maxn];
void PolyMul(int aLen, int a[], int bLen, int b[], int c[]) // c \not \in \{a, b\}
{
	static complex X[maxm], Y[maxm], tr = complex(0, -0.25);
	int cLen = aLen + bLen, len;
	for(len = 1; len < cLen; len <<= 1);
	if(std::min(aLen, bLen) <= nlim)
	{
		for(int i = 0; i < len; ++i)
			X[i] = complex(i < aLen ? a[i] : 0, i < bLen ? b[i] : 0);
		FFT(len, X, 1);
		for(int i = 0, j = (len - i) & (len - 1); i < len; j = (len - (++i)) & (len - 1))
			Y[i] = (X[i].sqr() - X[j].sqr().conj()) * tr;
		FFT(len, Y, -1);
		for(int i = 0; i < cLen; ++i)
			c[i] = (LL)(Y[i].r + 0.5) % mod;
		return;
	}
	for(int i = 0; i < len; ++i) // aLow * bLow
		X[i] = complex(i < aLen ? a[i] & msk : 0, i < bLen ? b[i] & msk : 0);
	FFT(len, X, 1);
	for(int i = 0, j = (len - i) & (len - 1); i < len; j = (len - (++i)) & (len - 1))
		Y[i] = (X[i].sqr() - X[j].sqr().conj()) * tr;
	FFT(len, Y, -1);
	for(int i = 0; i < cLen; ++i)
		c[i] = (LL)(Y[i].r + 0.5) % mod;
	for(int i = 0; i < len; ++i) // aLow * bUpp << sp
		X[i] = complex(i < aLen ? a[i] & msk : 0, i < bLen ? b[i] >> sp : 0);
	FFT(len, X, 1);
	for(int i = 0, j = (len - i) & (len - 1); i < len; j = (len - (++i)) & (len - 1))
		Y[i] = (X[i].sqr() - X[j].sqr().conj()) * tr;
	FFT(len, Y, -1);
	for(int i = 0; i < cLen; ++i)
		c[i] = (c[i] + ((LL)(Y[i].r + 0.5) << sp)) % mod;
	for(int i = 0; i < len; ++i) // aUpp * bLow << sp
		X[i] = complex(i < aLen ? a[i] >> sp : 0, i < bLen ? b[i] & msk : 0);
	FFT(len, X, 1);
	for(int i = 0, j = (len - i) & (len - 1); i < len; j = (len - (++i)) & (len - 1))
		Y[i] = (X[i].sqr() - X[j].sqr().conj()) * tr;
	FFT(len, Y, -1);
	for(int i = 0; i < cLen; ++i)
		c[i] = (c[i] + ((LL)(Y[i].r + 0.5) << sp)) % mod;
	for(int i = 0; i < len; ++i) // aUpp * bUpp * sd
		X[i] = complex(i < aLen ? a[i] >> sp : 0, i < bLen ? b[i] >> sp : 0);
	FFT(len, X, 1);
	for(int i = 0, j = (len - i) & (len - 1); i < len; j = (len - (++i)) & (len - 1))
		Y[i] = (X[i].sqr() - X[j].sqr().conj()) * tr;
	FFT(len, Y, -1);
	for(int i = 0; i < cLen; ++i)
		c[i] = (c[i] + (LL)(Y[i].r + 0.5) % mod * sd) % mod;
}
int main()
{
	for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i)
	{
		int j = i, k = ilim >> 1; // 2 pi / ilim
		for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
		w[i] = complex(cos(pi / k * j), sin(pi / k * j));
	}
	scanf("%d%d", &n, &mod);
	nlim = maxv / mod / mod;
	for(sp = 2; 1 << sp < mod; sp += 2);
	sd = (1 << sp) % mod;
	sp >>= 1;
	msk = (1 << sp) - 1;
	inv[1] = 1;
	for(int i = 2; i < n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	fact[0] = 1;
	for(int i = 1; i < n; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	static int f[maxm], f_ivs[maxm], dg_ivs[maxm];
	static int a[maxm], b[maxm], c[maxm];
	f[0] = f_ivs[0] = dg_ivs[0] = 1;
	for(int len = 2; (len >> 1) < n; len <<= 1)
	{
		// before here, we know f(x), 1/f(x), 1/g'(f(x)) (mod x^(len/2))
		// a = 2 - f * f_ivs
		PolyMul(len >> 1, f, len >> 1, f_ivs, a); // a[0] = 1
		for(int i = 1; i < len; ++i)
			if(a[i])
				a[i] = mod - a[i];
		// b = a * f_ivs
		PolyMul(len, a, len >> 1, f_ivs, b);
		// a = df
		for(int i = 1; i < len >> 1; ++i)
			a[i - 1] = (LL)f[i] * i % mod;
		// c = int(a * b)
		PolyMul((len >> 1) - 1, a, len, b, c);
		for(int i = len - 1; i > 0; --i) // i may > n
			c[i] = (LL)c[i - 1] * inv[i] % mod;
		c[0] = 0;
		// a = f * c + f
		PolyMul(len >> 1, f, len, c, a);
		for(int i = 0; i < len; ++i)
			if((a[i] += f[i]) >= mod)
				a[i] -= mod;
		// b = shift(shift(f * f / 2, 1) - a, 1) + c (only [len/2, len) is non-zero)
		b[0] = c[0];
		if((b[1] = c[1] - a[0]) < 0)
			b[1] += mod;
		PolyMul(len >> 1, f, len >> 1, f, b + 2);
		for(int i = 2; i < len; ++i)
			if((b[i] = ((LL)b[i] * inv[2] - a[i - 1] + c[i]) % mod) < 0)
				b[i] += mod;
		// a = b * dg_ivs, f = f - a (only modify [len/2, len) on a, f)
		PolyMul(len >> 1, b + (len >> 1), len >> 1, dg_ivs, a + (len >> 1));
		for(int i = len >> 1; i < len; ++i)
			f[i] = a[i] ? mod - a[i] : 0;
		// a = 2 - f * f_ivs
		PolyMul(len, f, len >> 1, f_ivs, a); // a[0] = 1
		for(int i = 1; i < len; ++i)
			if(a[i])
				a[i] = mod - a[i];
		// b = a * f_ivs, f_ivs = b
		PolyMul(len, a, len >> 1, f_ivs, b);
		memcpy(f_ivs, b, len * sizeof(int));
		// a = df
		for(int i = 1; i < len; ++i)
			a[i - 1] = (LL)f[i] * i % mod;
		// b = int(a * f_ivs) + 2
		PolyMul(len - 1, a, len, f_ivs, b);
		for(int i = len - 1; i > 0; --i) // i may > n
			b[i] = (LL)b[i - 1] * inv[i] % mod;
		b[0] = 2;
		// a = shift(shift(f, 1) - b, 1) + f_ivs
		a[0] = f_ivs[0];
		if((a[1] = f_ivs[1] - b[0]) < 0)
			a[1] += mod;
		for(int i = 2; i < len; ++i)
			if((a[i] = f[i - 2] - b[i - 1] + f_ivs[i]) >= mod)
				a[i] -= mod;
			else if(a[i] < 0)
				a[i] += mod;
		// b = 2 - a * dg_ivs
		PolyMul(len, a, len, dg_ivs, b); // b[0] = 1
		for(int i = 1; i < len; ++i)
			if(b[i])
				b[i] = mod - b[i];
		// c = b * dg_ivs, dg_ivs = c
		PolyMul(len, b, len >> 1, dg_ivs, c);
		memcpy(dg_ivs, c, len * sizeof(int));
	}
	for(int i = 0; i < n; ++i)
	{
		f[i] = (LL)f[i] * fact[i] % mod;
		printf("%d\n", f[i]);
	}
	return 0;
}
