#include <cmath>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50001, maxm = 65536;
const long double pi = acos(-1.0);
struct complex
{
	long double r, i;
	complex() {}
	complex(long double x, long double y) : r(x), i(y) {}
	friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
	friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
	friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
} X1[maxm], X2[maxm], Y1[maxm], Y2[maxm], t[maxm];
void FFT(complex a[], int n, int flag)
{
	for(int i = 1, j = n >> 1, k; i < n - 1; ++i)
	{
		if(i < j)
			swap(a[i], a[j]);
		for(k = n >> 1; j >= k; k >>= 1)
			j -= k;
		if(j < k)
			j += k;
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
const int mod = 1000000007, mod2 = 31623, mod3 = 14122;
int inv[maxn];
int n, m, ans[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		X1[i] = complex(x % mod2, 0);
		X2[i] = complex(x / mod2, 0);
	}
	for(int i = 0, x = 1; i < n; ++i)
	{
		Y1[i] = complex(x % mod2, 0);
		Y2[i] = complex(x / mod2, 0);
		x = (LL)x * (m + i) % mod * inv[i + 1] % mod;
	}
	int len = 1;
	for( ; len < n << 1; len <<= 1);
	FFT(X1, len, 1);
	FFT(X2, len, 1);
	FFT(Y1, len, 1);
	FFT(Y2, len, 1);
	for(int i = 0; i < len; ++i)
		t[i] = X1[i] * Y1[i];
	FFT(t, len, -1);
	for(int i = 0; i < n; ++i)
		ans[i] = (LL)(t[i].r + 0.5) % mod;
	for(int i = 0; i < len; ++i)
		t[i] = X1[i] * Y2[i] + X2[i] * Y1[i];
	FFT(t, len, -1);
	for(int i = 0; i < n; ++i)
		ans[i] = (ans[i] + (LL)(t[i].r + 0.5) % mod * mod2) % mod;
	for(int i = 0; i < len; ++i)
		t[i] = X2[i] * Y2[i];
	FFT(t, len, -1);
	for(int i = 0; i < n; ++i)
		ans[i] = (ans[i] + (LL)(t[i].r + 0.5) % mod * mod3) % mod;
	for(int i = 0; i < n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
