#include <cstdio>
typedef long long LL;
const int maxn = 1001, maxm = 4001, mod = 998244353;
int fact[maxm], iact[maxm], a[4], f[3][maxm];
void conv(int alen, int a[], int blen, int b[], int f[]) {
    for(int i = 0; i < alen + blen - 1; ++i)
        f[i] = 0;
    for(int i = 0; i < alen; ++i)
        for(int j = 0; j < blen; ++j)
            f[i + j] = (f[i + j] + (LL)a[i] * b[j]) % mod;
}
int main() {
    iact[1] = 1;
    for(int i = 2; i < maxm; ++i)
        iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
    fact[0] = iact[0] = 1;
    for(int i = 1; i < maxm; ++i) {
        fact[i] = (LL)fact[i - 1] * i % mod;
        iact[i] = (LL)iact[i - 1] * iact[i] % mod;
    }
    while(scanf("%d%d%d%d", a + 0, a + 1, a + 2, a + 3) == 4) {
        int cur = 0, pre = 1, sz = 1;
        f[cur][0] = 1;
        for(int i = 0; i < 4; ++i) {
            if(!a[i])
                continue;
            pre ^= 1;
            cur ^= 1;
            for(int j = 1; j <= a[i]; ++j)
                f[2][j] = (LL)fact[a[i] - 1] * iact[j - 1] % mod * iact[a[i] - j] % mod * iact[j] % mod;
            conv(sz, f[pre], a[i] + 1, f[2], f[cur]);
            sz += a[i];
        }
        int ans = 0;
        for(int i = 0; i < sz; ++i) {
            f[cur][i] = (LL)f[cur][i] * fact[i] % mod;
            if((sz - i) & 1)
                (ans += f[cur][i]) >= mod && (ans -= mod);
            else
                (ans -= f[cur][i]) < 0 && (ans += mod);
        }
        printf("%d\n", ans);
    }
    return 0;
}
