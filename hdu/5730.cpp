#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, maxm = 131072, mod = 313;
const long double pi = acos(-1.0);
struct complex
{
    long double r, i;
    complex() {}
    complex(long double x, long double y) : r(x), i(y) {}
    friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
    friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
    friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
} x[maxm], y[maxm];
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
int n, f[maxn], g[maxn];
void solve(int L, int R)
{
    if(L == R)
        return;
    int M = (L + R) >> 1;
    solve(L, M);
    int len, plen = R - L + 1;
    for(len = 1; len < plen; len <<= 1);
    for(int i = 0; i < len; ++i)
    {
        x[i] = i < plen ? complex(f[i], 0) : complex(0, 0);
        y[i] = L + i <= M ? complex(g[L + i], 0) : complex(0, 0);
    }
    FFT(x, len, 1);
    FFT(y, len, 1);
    for(int i = 0; i < len; ++i)
        x[i] = x[i] * y[i];
    FFT(x, len, -1);
    for(int i = M + 1; i <= R; ++i)
        g[i] = (g[i] + (LL)(x[i - L].r + 0.5)) % mod;
    solve(M + 1, R);
}
int main()
{
    while(scanf("%d", &n) == 1 && n)
    {
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", f + i);
            f[i] %= mod;
        }
        g[0] = 1;
        memset(g + 1, 0, n * sizeof(int));
        solve(0, n);
        printf("%d\n", g[n]);
    }
    return 0;
}
