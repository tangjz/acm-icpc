#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 14001, maxk = 11, maxLen = 17, maxm = 1 << maxLen | 1, mod = 786433, gen = 10;
int inv[mod], w[maxm], fact[maxm], iact[maxm], ivs, bitLen, bitRev[maxm];
int t, p, n, m, q, a[maxk][maxn], f[maxk][maxm], cnt[maxm], prd[maxm], g[maxm];
inline int mod_add(int x, int y) {
    return (x += y) < mod ? x : x - mod;
}
inline int mod_sub(int x, int y) {
    return (x -= y) < 0 ? x + mod : x;
}
int mod_pow(int x, int k) {
    int ret = 1;
    for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
        (k & 1) && (ret = (LL)ret * x % mod);
    return ret;
}
void NTT(int len, int x[], int flag) {
    for(int i = 1; i < len; ++i)
        if(i < bitRev[i])
            std::swap(x[i], x[bitRev[i]]);
    for(int i = 1, d = 1; d < len; ++i, d <<= 1)
        for(int j = 0; j < len; j += d << 1)
            for(int k = 0, *X = x + j; k < d; ++k) {
                int t = (LL)w[k << (maxLen - i)] * X[k + d] % mod;
                X[k + d] = mod_sub(X[k], t);
                X[k] = mod_add(X[k], t);
            }
    if(flag == -1) {
        std::reverse(x + 1, x + len);
        for(int i = 0; i < len; ++i)
            x[i] = (LL)x[i] * ivs % mod;
    }
}
int main() {
    inv[1] = 1;
    for(int i = 2; i < mod; ++i)
        inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
    w[0] = fact[0] = fact[1] = iact[0] = iact[1] = 1;
    w[1] = mod_pow(gen, (mod - 1) >> maxLen);
    for(int i = 2; i < (1 << maxLen); ++i) {
        w[i] = (LL)w[i - 1] * w[1] % mod;
        fact[i] = (LL)fact[i - 1] * i % mod;
        iact[i] = (LL)iact[i - 1] * inv[i] % mod;
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &p, &n, &q);
        for(m = 1; m <= (p - 1) * n; m <<= 1);
        ivs = inv[m];
        for(bitLen = 0; (1 << bitLen) < m; ++bitLen);
        for(int i = 1; i < m; ++i)
            bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
        memset(cnt, 0, m * sizeof(int));
        for(int i = 0; i < m; ++i)
            prd[i] = 1;
        for(int i = 1; i < p; ++i) {
            for(int j = 0; j <= n; ++j) {
                scanf("%1d", a[i] + j);
                f[i][j] = a[i][j] ? iact[j] : 0;
            }
            memset(f[i] + n + 1, 0, (m - n - 1) * sizeof(int));
            NTT(m, f[i], 1);
            for(int j = 0; j < m; ++j)
                f[i][j] ? (prd[j] = (LL)prd[j] * f[i][j] % mod) : ++cnt[j];
        }
        for(int i = 0; i < m; ++i)
            g[i] = cnt[i] ? 0 : prd[i];
        while(q--) {
            int x, y;
            scanf("%d%d", &x, &y);
            int dt = a[x][y] ? mod - iact[y] : iact[y], seed = w[y << (maxLen - bitLen)];
            for(int i = 0; i < m; ++i, dt = (LL)dt * seed % mod) {
                f[x][i] ? (prd[i] = (LL)prd[i] * inv[f[x][i]] % mod) : --cnt[i];
                f[x][i] = mod_add(f[x][i], dt);
                f[x][i] ? (prd[i] = (LL)prd[i] * f[x][i] % mod) : ++cnt[i];
                if(!cnt[i])
                    g[i] = mod_add(g[i], prd[i]);
            }
            a[x][y] ^= 1;
        }
        NTT(m, g, -1);
        int ans = 0;
        for(int i = 1; i < m; ++i)
            ans = (ans + (LL)g[i] * fact[i]) % mod;
        printf("%d\n", ans);
    }
    return 0;
}