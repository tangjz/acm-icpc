#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, maxm = 1 << 18, mod = 1000000007;
const double pi = acos(-1.0);
struct complex
{
	double r, i;
	complex() {}
	complex(double x, double y) : r(x), i(y) {}
	friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
	friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
	friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
	complex conj() const { return complex(r, -i); }
} x[maxm], y[maxm];
void FFT(complex a[], int n, int flag) // dft(flag = 1), idft(flag = 0)
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
int n, len, pw[maxn], f[maxn << 1], h[maxn << 1], ans;
char str[maxn], buf[maxn << 1];
int main()
{
	scanf("%s", str);
	n = strlen(str);
	pw[0] = 1;
	for(int i = 1; i <= n + 1 >> 1; ++i)
		if((pw[i] = pw[i - 1] << 1) >= mod)
			pw[i] -= mod;
	for(len = 1; len < n << 1; len <<= 1);
	for(char ch = 'a'; ch <= 'b'; ++ch)
	{
		for(int i = 0; i < len; ++i)
		{
			int v = i < n && str[i] == ch;
			x[i] = complex(v, v);
		}
		FFT(x, len, 1);
		for(int i = 0; i < len; ++i)
		{
			int v = (len - i) & (len - 1);
			y[i] = (x[i] * x[i] - (x[v] * x[v]).conj()) * complex(0, -0.25);
		}
		FFT(y, len, -1);
		for(int i = 0; i <= n - 1 << 1; ++i)
			f[i] += (int)(y[i].r + 0.5);
	}
	for(int i = 0; i < n; ++i)
	{
		buf[i << 1] = str[i];
		buf[i << 1 | 1] = '#';
	}
	buf[n - 1 << 1 | 1] = '\0';
	for(int i = 0, mx = 0, id = 0; i <= n - 1 << 1; ++i)
	{
		h[i] = i < mx ? std::min(mx - i, h[(id << 1) - i]) : 0;
		for( ; h[i] <= i && buf[i - h[i]] == buf[i + h[i]]; ++h[i]);
		if(mx < i + h[i])
		{
			mx = i + h[i];
			id = i;
		}
	}
	for(int i = 0; i <= n - 1 << 1; ++i)
	{
		if((ans += pw[f[i] + 1 >> 1] - 1) >= mod)
			ans -= mod;
		if((ans -= h[i] - (i & 1) - (~(i - h[i]) & 1) + 1 >> 1) < 0)
			ans += mod;
	}
	printf("%d\n", ans);
	return 0;
}
