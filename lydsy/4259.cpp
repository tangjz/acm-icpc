#include <cmath>
#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 300001, maxm = 1 << 20, maxd = 26;
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
int n, m, len, cnt, out[maxn];
char s[maxn], t[maxn];
LL f[maxm];
inline int trans(char ch)
{
	return ch == '*' ? 0 : (ch < 'a' + (maxd >> 1) ? ch - 'a' + 1 : ch - 'z' - 1);
}
inline int Squ(int x)
{
	return x * x;
}
inline int Cub(int x)
{
	return x * x * x;
}
int main()
{
	scanf("%d%d%s%s", &n, &m, s, t);
	std::reverse(s, s + n);
	for(len = 1; len < n + m; len <<= 1);
	// + 3 1
	for(int i = 0; i < len; ++i)
		X[i] = complex(i < n ? Cub(trans(s[i])) : 0, i < m ? trans(t[i]) : 0);
	FFT(X, len, 1);
	for(int i = 0; i < len; ++i)
	{
		int j = (len - i) & (len - 1);
		Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
	}
	FFT(Y, len, -1);
	for(int i = 0; i <= m - n; ++i)
		f[i] += (LL)(Y[n - 1 + i].r + 0.5);
	// + 1 3
	for(int i = 0; i < len; ++i)
		X[i] = complex(i < n ? trans(s[i]) : 0, i < m ? Cub(trans(t[i])) : 0);
	FFT(X, len, 1);
	for(int i = 0; i < len; ++i)
	{
		int j = (len - i) & (len - 1);
		Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
	}
	FFT(Y, len, -1);
	for(int i = 0; i <= m - n; ++i)
		f[i] += (LL)(Y[n - 1 + i].r + 0.5);
	// - 2 2
	for(int i = 0; i < len; ++i)
		X[i] = complex(i < n ? Squ(trans(s[i])) : 0, i < m ? Squ(trans(t[i])) : 0);
	FFT(X, len, 1);
	for(int i = 0; i < len; ++i)
	{
		int j = (len - i) & (len - 1);
		Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
	}
	FFT(Y, len, -1);
	for(int i = 0; i <= m - n; ++i)
	{
		f[i] -= (LL)(Y[n - 1 + i].r + 0.5) << 1;
		if(!f[i])
			out[cnt++] = i + 1;
	}
	printf("%d\n", cnt);
	for(int i = 0; i < cnt; ++i)
		printf("%d%c", out[i], " \n"[i == cnt - 1]);
	return 0;
}
