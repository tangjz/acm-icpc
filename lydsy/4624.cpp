#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 501, maxm = 1 << 19;
const long double pi = acos(-1.0);
struct complex
{
	long double r, i;
	complex() {}
	complex(long double x, long double y) : r(x), i(y) {}
	friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
	friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
	friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
} X1[maxm], X2[maxm], Y1[maxm], Y2[maxm];
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
int n, m, tt, p, q, slen, tlen, len;
char s[maxn * maxn], t[maxn * maxn];
int main()
{
	scanf("%d%d", &n, &m);
	slen = n * m;
	for(int i = 0; i < n; ++i)
		scanf("%s", s + i * m);
	for(int i = 0; i < slen; ++i)
		(s[i] == 'G' ? X1[i] : X2[i]) = complex(1, 0);
	for(len = 1; len < slen << 1; len <<= 1);
	FFT(X1, len, 1);
	FFT(X2, len, 1);
	scanf("%d", &tt);
	for(int Case = 1; Case <= tt; ++Case)
	{
		scanf("%d%d", &p, &q);
		tlen = (p - 1) * m + q;
		for(int i = 0; i < p; ++i)
			scanf("%s", t + i * m);
		for(int i = 0, j = 0; i < tlen; ++i, j = j + 1 < m ? j + 1 : 0)
			Y1[i] = complex(j < q && t[i] == 'G', 0);
		for(int i = tlen; i < len; ++i)
			Y1[i] = complex(0, 0);
		reverse(Y1, Y1 + tlen);
		FFT(Y1, len, 1);
		for(int i = 0; i < len; ++i)
			Y1[i] = X1[i] * Y1[i];
		FFT(Y1, len, -1);
		for(int i = 0, j = 0; i < tlen; ++i, j = j + 1 < m ? j + 1 : 0)
			Y2[i] = complex(j < q && t[i] == 'L', 0);
		for(int i = tlen; i < len; ++i)
			Y2[i] = complex(0, 0);
		reverse(Y2, Y2 + tlen);
		FFT(Y2, len, 1);
		for(int i = 0; i < len; ++i)
			Y2[i] = X2[i] * Y2[i];
		FFT(Y2, len, -1);
		int ans = -1, pos, s1;
		for(int i = tlen - 1, j = 0; i < slen; ++i, j = j + 1 < m ? j + 1 : 0)
			if(j + q <= m && ans < (int)(Y1[i].r + 0.5) + (int)(Y2[i].r + 0.5))
			{
				pos = i - tlen + 1;
				s1 = (int)(Y1[i].r + 0.5);
				ans = s1 + (int)(Y2[i].r + 0.5);
			}
		printf("Case #%d: %d %d %d %d\n", Case, pos / m + 1, pos % m + 1, s1, ans - s1);
	}
	return 0;
}
