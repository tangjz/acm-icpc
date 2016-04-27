#include <cmath>
#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, maxm = 262144;
const long double pi = acos(-1.0);
struct Complex
{
	long double r, i;
	Complex() {}
	Complex(long double x, long double y) : r(x), i(y) {}
	friend Complex operator + (const Complex &a, const Complex &b) { return Complex(a.r + b.r, a.i + b.i); }
	friend Complex operator - (const Complex &a, const Complex &b) { return Complex(a.r - b.r, a.i - b.i); }
	friend Complex operator * (const Complex &a, const Complex &b) { return Complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
} FFTx[maxm], FFTy[maxm];
void FFT(Complex a[], int n, int flag)
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
		Complex wn(cos(pi / i), flag * sin(pi / i));
		for(int j = 0; j < n; j += i << 1)
		{
			Complex w(1, 0);
			for(int k = 0; k < i; ++k, w = w * wn)
			{
				Complex t = w * a[j + k + i];
				a[j + k + i] = a[j + k] - t;
				a[j + k] = a[j + k] + t;
			}
		}
	}
	if(flag == -1)
		for(int i = 0; i < n; ++i)
			a[i].r /= n;
}
int main()
{
	int n, len;
	scanf("%d", &n);
	for(len = 1; len < n << 1; len <<= 1);
	for(int i = 0; i < n; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		FFTx[i] = Complex(a, 0);
		FFTy[n - 1 - i] = Complex(b, 0);
	}
	FFT(FFTx, len, 1);
	FFT(FFTy, len, 1);
	for(int i = 0; i < len; ++i)
		FFTx[i] = FFTx[i] * FFTy[i];
	FFT(FFTx, len, -1);
	for(int i = 0; i < n; ++i)
		printf("%d\n", (int)(FFTx[n - 1 + i].r + 0.5));
	return 0;
}
