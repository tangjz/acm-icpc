#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxm = 1 << 18;
const long double pi = acos(-1.0);
struct complex
{
	long double r, i;
	complex() {}
	complex(long double x, long double y) : r(x), i(y) {}
	friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
	friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
	friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
	complex conj() { return complex(r, -i); }
} X[maxm], Y[maxm];
void FFT(complex a[], int n, int flag)
{
	for(int i = 1, j = n >> 1, k; i < n - 1; ++i)
	{
		if(i < j)
			std::swap(a[i], a[j]);
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
int t, n, len, a[maxm], b[maxm];
LL f[maxm], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(len = 1; len < n << 1; len <<= 1);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		std::reverse(a, a + n);
		memset(a + n, 0, (len - n) * sizeof(int));
		for(int i = 0; i < n; ++i)
			scanf("%d", b + i);
		memcpy(b + n, b, n * sizeof(int));
		memset(b + (n << 1), 0, (len - (n << 1)) * sizeof(int));
		// large
		for(int i = 0; i < len; ++i)
			X[i] = complex(a[i] >> 10, b[i] >> 10);
		FFT(X, len, 1);
		for(int i = 0; i < len; ++i)
		{
			int j = (len - i) & (len - 1);
			Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
		}
		FFT(Y, len, -1);
		for(int i = 0, j = n - 1; i < n; ++i, ++j)
			f[i] = (LL)(Y[j].r + 0.5) << 20;
		// small
		for(int i = 0; i < len; ++i)
			X[i] = complex(a[i] & ((1 << 10) - 1), b[i] & ((1 << 10) - 1));
		FFT(X, len, 1);
		for(int i = 0; i < len; ++i)
		{
			int j = (len - i) & (len - 1);
			Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
		}
		FFT(Y, len, -1);
		for(int i = 0, j = n - 1; i < n; ++i, ++j)
			f[i] += (LL)(Y[j].r + 0.5);
		// middle 1
		for(int i = 0; i < len; ++i)
			X[i] = complex(a[i] >> 10, b[i] & ((1 << 10) - 1));
		FFT(X, len, 1);
		for(int i = 0; i < len; ++i)
		{
			int j = (len - i) & (len - 1);
			Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
		}
		FFT(Y, len, -1);
		for(int i = 0, j = n - 1; i < n; ++i, ++j)
			f[i] += (LL)(Y[j].r + 0.5) << 10;
		// middle 2
		for(int i = 0; i < len; ++i)
			X[i] = complex(a[i] & ((1 << 10) - 1), b[i] >> 10);
		FFT(X, len, 1);
		for(int i = 0; i < len; ++i)
		{
			int j = (len - i) & (len - 1);
			Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
		}
		FFT(Y, len, -1);
		ans = 0;
		for(int i = 0, j = n - 1; i < n; ++i, ++j)
		{
			f[i] += (LL)(Y[j].r + 0.5) << 10;
			if(ans < f[i])
				ans = f[i];
		}
		// calc
		ans = -ans << 1;
		for(int i = 0; i < n; ++i)
			ans += (LL)a[i] * a[i] + (LL)b[i] * b[i];
		printf("%lld\n", ans);
	}
	return 0;
}
