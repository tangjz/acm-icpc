#include <cmath>
#include <cstdio>
#include <algorithm>
const int maxn = 500001, maxm = 1 << 20;
const long double pi = acos(-1.0);
struct complex
{
	long double r, i;
	complex() {}
	complex(long double x, long double y) : r(x), i(y) {}
	friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
	friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
	friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
} FFTx[maxm];
void FFT(complex a[], int n, int flag)
{
	static int bitlen, bitrev[maxm];
	for(bitlen = 0; 1 << bitlen < n; ++bitlen);
	for(int i = 1; i < n; ++i)
	{
		bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (bitlen - 1));
		if(i < bitrev[i])
			std::swap(a[i], a[bitrev[i]]);
	}
	for(int i = 1; i < n; i <<= 1)
	{
		complex wn(cos(pi / i), flag * sin(pi / i));
		for(int j = 0; j < n; j += i << 1)
		{
			complex w(1, 0);
			for(int k = 0; k < i; ++k, w = w * wn)
			{
				complex t = w * a[j + k + i];
				a[j + k + i] = a[j + k] - t;
				a[j + k] = a[j + k] + t;
			}
		}
	}
	if(flag == -1)
		for(int i = 0; i < n; ++i)
			a[i].r /= n;
}
int tot, prime[maxn], d[maxn], c[maxn], s[maxn], seg[maxm];
long long f[maxn];
bool vis[maxn];
inline int seg_idx(int L, int R)
{
	return L + R | L != R;
}
void build(int L, int R)
{
	int o = seg_idx(L, R);
	if(L == R)
	{
		seg[o] = L;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	build(L, M);
	build(M + 1, R);
	seg[o] = f[seg[lch]] >= f[seg[rch]] ? seg[lch] : seg[rch];
}
int query(int L, int R, int l, int r)
{
	int o = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[o];
	int M = L + R >> 1, ret = -1, tmp;
	if(l <= M)
		ret = query(L, M, l, r);
	if(r > M)
	{
		tmp = query(M + 1, R, l, r);
		if(ret == -1 || f[ret] < f[tmp])
			ret = tmp;
	}
	return ret;
}
int main()
{
	d[1] = s[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			d[i] = 1;
			c[i] = 1;
			s[i] = 2;
		}
		for(int j = 0; j < tot && (long long)i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				d[i * prime[j]] = d[i];
				c[i * prime[j]] = c[i] + 1;
				s[i * prime[j]] = s[d[i]] * (c[i * prime[j]] + 1);
				break;
			}
			else
			{
				d[i * prime[j]] = i;
				c[i * prime[j]] = 1;
				s[i * prime[j]] = s[i] * 2;
			}
		}
	}
	for(int i = 0; i < maxm; ++i)
		FFTx[i] = complex(i < maxn ? s[i] : 0, 0);
	FFT(FFTx, maxm, 1);
	for(int i = 0; i < maxm; ++i)
		FFTx[i] = FFTx[i] * FFTx[i];
	FFT(FFTx, maxm, -1);
	for(int i = 1; i < maxn; ++i)
		f[i] = (long long)(FFTx[i].r + 0.5);
	build(1, maxn - 1);
	int t, l, r;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &l, &r);
		int idx = query(1, maxn - 1, l, r);
		printf("%d %lld\n", idx, f[idx]);
	}
	return 0;
}
