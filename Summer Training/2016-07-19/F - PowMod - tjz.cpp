#include <map>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 10000001, mod = 1000000007, maxd = 8;
int tot, prime[maxn >> 3], d[maxn], phi[maxn], s[maxn];
int n, m, p, sz, fact[maxd], all, f[1 << maxd], ans;
std::map<int, int> g[1 << maxd];
int G(int msk, int val)
{
    if(val <= 1)
        return val ? phi[f[msk]] : 0;
    if(!msk)
        return s[val];
    if(g[msk].count(val))
        return g[msk][val];
    int ret = (LL)phi[f[msk]] * G(0, val) % mod;
    for(int i = msk; i; i = (i - 1) & msk)
        ret = (ret + (LL)phi[f[msk ^ i]] * G(i, val / f[i])) % mod;
    return g[msk][val] = ret;
}
int mod_pow(int x, int k, int p)
{
    int ret = 1 % p;
    for( ; k > 0; k >>= 1, x = (LL)x * x % p)
        if(k & 1)
            ret = (LL)ret * x % p;
    return ret;
}
int calc(int x, int p)
{
    return p == 1 ? 0 : mod_pow(x, calc(x, phi[p]) + phi[p], p);
}
int main()
{
    phi[1] = s[1] = 1;
    for(int i = 2; i < maxn; ++i)
    {
        if(!d[i])
        {
            prime[tot++] = d[i] = i;
            phi[i] = i - 1;
        }
        for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
            if(i % prime[j])
            {
                d[i * prime[j]] = prime[j];
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
            else
            {
                d[i * prime[j]] = prime[j];
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        if((s[i] = s[i - 1] + phi[i]) >= mod)
            s[i] -= mod;
    }
    while(scanf("%d%d%d", &n, &m, &p) == 3)
    {
        sz = 0;
        for(int tmp = n; tmp > 1; fact[sz++] = d[tmp], tmp /= d[tmp]);
        all = (1 << sz) - 1;
        f[0] = 1;
        for(int i = 1, j = 0; i <= all; ++i)
        {
            int lbt = i & -i;
            if(lbt == i)
                f[i] = fact[j++];
            else
                f[i] = f[lbt] * f[i ^ lbt];
        }
        for(int i = 1; i <= all; ++i)
            std::map<int, int>().swap(g[i]);
        ans = G(all, m);
        printf("%d\n", calc(ans, p));
    }
    return 0;
}

