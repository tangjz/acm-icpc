#include <cstdio>
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
int n, f[maxn], g[maxn], s[maxn];
inline LL sum2(int n)
{
    return n * (n + 1LL) >> 1;
}
inline LL sum3(int n)
{
    LL v1 = sum2(n);
    int v2 = n + 2;
    (v2 % 3 ? v1 /= 3 : v2 /= 3);
    return v1 % mod * v2;
}
int main()
{
    f[1] = g[0] = s[0] = g[1] = 1;
    s[1] = 2;
    for(int i = 2; i < maxn; ++i)
    {
        g[i] = (sum2(g[i - 1]) + (LL)g[i - 1] * s[i - 2]) % mod;
        if((s[i] = s[i - 1] + g[i]) >= mod)
            s[i] -= mod;
        f[i] = i & 1 ? (sum2(g[i >> 1]) % mod * s[(i >> 1) - 1] + sum3(g[i >> 1])) % mod : sum2(g[i >> 1]) % mod;
    }
    while(scanf("%d", &n) == 1 && n)
        printf("%d\n", f[n]);
    return 0;
}
