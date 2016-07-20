#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 30001, maxm = 1 << 16, seed = 233, mod = 1000000007;
const double pi = acos(-1.0);
struct complex
{
	long double r, i;
	complex() {}
	complex(long double x, long double y) : r(x), i(y) {}
	friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
	friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
	friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
	complex conj() { return complex(r, -i); }
} X[maxm];
int len, bitlen, bitrev[maxm];
void FFT(complex a[], int n, int flag)
{
	for(int i = 1; i < len; ++i)
		if(i < bitrev[i])
			std::swap(a[i], a[bitrev[i]]);
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
int t, n, a[maxn], s, bsize, f[maxn], g[maxn], rk[maxn], ansl[maxn], ansr[maxn];
std::vector<int> pos[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			a[i] += a[i - 1];
			pos[a[i]].push_back(i);
		}
		s = a[n];
		for(bitlen = 0, len = 1; len <= s << 1; ++bitlen, len <<= 1);
		for(int i = 1; i < len; ++i)
			bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (bitlen - 1));
		bsize = (int)ceil(sqrt(n * bitlen * 100));
		memset(f, 0, (s + 1) * sizeof(int));
		memset(g, 0, (s + 1) * sizeof(int));
		for(int i = 1; i <= n; ++i)
		{
			++f[a[i]];
			++g[s - a[i - 1]];
		}
		for(int i = 0; i < len; ++i)
			X[i] = i <= s ? complex(f[i] + g[i], f[i] - g[i]) : complex(0, 0);
		FFT(X, len, 1);
		for(int i = 0; i < len; ++i)
			X[i] = X[i] * X[i];
		FFT(X, len, -1);
		for(int i = 1; i <= s; ++i)
		{
			int val = (int)(X[s + i].r + 0.5) >> 2;
			rk[i] = val + 1 >> 1;
			if(!rk[i])
				ansl[i] = ansr[i] = 0;
		}
		memset(g, 0, (s + 1) * sizeof(int));
		for(int i = 1; i <= n; i += bsize)
		{
			int lim = i + bsize - 1 < n ? i + bsize - 1 : n;
			for(int j = i; j <= lim; ++j)
				++g[s - a[j - 1]];
			for(int j = 0; j < len; ++j)
				X[j] = j <= s ? complex(f[j] + g[j], f[j] - g[j]) : complex(0, 0);
			FFT(X, len, 1);
			for(int j = 0; j < len; ++j)
				X[j] = X[j] * X[j];
			FFT(X, len, -1);
			for(int j = 1; j <= s; ++j)
			{
				if(!rk[j])
					continue;
				int val = (int)(X[s + j].r + 0.5) >> 2;
				if(rk[j] > val)
					rk[j] -= val;
				else
				{
					for(int k = i; k <= lim; ++k)
						if(rk[j] > f[a[k - 1] + j])
							rk[j] -= f[a[k - 1] + j];
						else
						{
							ansl[j] = k;
							ansr[j] = pos[a[k - 1] + j][rk[j] - 1];
							rk[j] = 0;
							break;
						}
				}
			}
			for(int j = i; j <= lim; ++j)
				--g[s - a[j - 1]];
		}
		int ansL = 0, ansR = 0;
		for(int i = 1, pw = 1; i <= s; ++i)
		{
			pw = (LL)pw * seed % mod;
			ansL = (ansL + (LL)pw * ansl[i]) % mod;
			ansR = (ansR + (LL)pw * ansr[i]) % mod;
		}
		printf("%d %d\n", ansL, ansR);
		for(int i = 1; i <= n; ++i)
			if(pos[a[i]].size() > 0)
				std::vector<int>().swap(pos[a[i]]);
	}
	return 0;
}
