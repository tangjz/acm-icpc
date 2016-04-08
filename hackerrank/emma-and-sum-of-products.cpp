#include <cmath>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 131072, mod = 100003;
const long double pi = acos(-1.0);
struct complex
{
	long double r, i;
	complex() {}
	complex(long double x, long double y) : r(x), i(y) {}
	friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
	friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
	friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
} FFTx[maxn], FFTy[maxn];
void FFT(complex a[], int n, int flag)
{
	static int bitlen, bitrev[maxn];
	for(bitlen = 0; 1 << bitlen < n; ++bitlen);
	for(int i = 1; i < n; ++i)
	{
		bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (bitlen - 1));
		if(i < bitrev[i])
			swap(a[i], a[bitrev[i]]);
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
int n, q, a[maxn >> 1], len, f[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(len = 1; len < n << 1; len <<= 1);
	for(int i = 0; i < len >> 1; ++i)
		if(i < n)
		{
			f[i << 1] = a[i];
			f[i << 1 | 1] = 1;
		}
		else
			f[i << 1] = 1;
	for(int delta = 2, size = delta << 1; delta < len; delta = size, size <<= 1)
		for(int i = 0; i < len; i += size)
		{
			for(int j = 0; j < size; ++j)
				FFTx[j] = complex(j < delta ? f[i + j] : 0, 0);
			for(int j = 0; j < size; ++j)
				FFTy[j] = complex(j < delta ? f[i + delta + j] : 0, 0);
			FFT(FFTx, size, 1);
			FFT(FFTy, size, 1);
			for(int j = 0; j < size; ++j)
				FFTx[j] = FFTx[j] * FFTy[j];
			FFT(FFTx, size, -1);
			for(int j = 0; j < size; ++j)
				f[i + j] = (LL)(FFTx[j].r + 0.5) % mod;
		}
	scanf("%d", &q);
	while(q--)
	{
		int k;
		scanf("%d", &k);
		printf("%d\n", f[n - k]);
	}
	return 0;
}
