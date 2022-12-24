#include <cstdio>
const int maxn = 1000001, mod = (int)1e9 + 7;
int mu[maxn], g[maxn], t, n;
long long f[maxn], dt;
int main() {
    for(int i = 1; i < maxn; ++i)
        for(int j = i; j < maxn; j += i)
            ++g[j];
    mu[1] = 1;
    for(int i = 1; i < maxn; ++i) {
        for(int j = i + i; j < maxn; j += i)
            mu[j] -= mu[i];
        if(!mu[i])
            continue;
        dt = 0;
        if(mu[i] > 0)
            for(int j = i, k = 1; j < maxn; j += i, ++k) {
                dt += 1 + g[k - 1];
                f[j] += dt;
            }
        else
            for(int j = i, k = 1; j < maxn; j += i, ++k) {
                dt += 1 + g[k - 1];
                f[j] -= dt;
            }
    }
    for(int i = 1; i < maxn; ++i)
        f[i] += f[i - 1];
    while(scanf("%d", &n) == 1)
        printf("%d\n", (int)(f[n] % mod));
    return 0;
}