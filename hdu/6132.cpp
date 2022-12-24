#include <cstring>
typedef long long LL;
const int maxp = 501, maxs = 250001, maxd = 11, mod = (int)1e9 + 7, inv2 = (mod + 1) >> 1;
int t, m, p, tot, pw[maxs], seq[maxs], pos[maxp][maxp], inv[maxd], c[maxp], f[maxd][maxp];
LL n;
int mod_inv(int x) {
    return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int mod_pow(int x, int k) {
    int ret = 1;
    for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
        (k & 1) && (ret = (LL)ret * x % mod);
    return ret;
}
int mod_sum(int x, LL k) {
    if(k <= 1)
        return k;
    if(x <= 1)
        return x * k % mod;
    return (mod_pow(x, k % (mod - 1)) - 1LL) * mod_inv(x - 1) % mod;
}
int main() {
    inv[1] = 1;
    for(int i = 2; i < maxd; ++i)
        inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
    scanf("%d", &t);
    while(t--) {
        scanf("%I64d%d%d%d", &n, &pw[1], &m, &p);
        memset(pos, 0, sizeof pos);
        memset(c, 0, sizeof c);
        seq[1] = pw[1] %= p;
        pos[pw[1]][seq[1]] = 1;
        for(int i = 2; i <= p * p; ++i) {
            pw[i] = pw[i - 1] * pw[1] % p;
            seq[i] = ((seq[i - 1] << 1) + pw[i]) % p;
            if(pos[pw[i]][seq[i]]) {
                int beg = pos[pw[i]][seq[i]], end = i, len = end - beg, stp = mod_pow(inv2, len);
                for(int j = 1; j < beg && j <= n; ++j)
                    (c[seq[j]] += mod_pow(2, (n - j) % (mod - 1))) >= mod && (c[seq[j]] -= mod);
                for(int j = beg; j < end && j <= n; ++j)
                    c[seq[j]] = (c[seq[j]] + (LL)mod_pow(2, (n - j) % (mod - 1)) * mod_sum(stp, (n - j) / len + 1)) % mod;
                break;
            }
            pos[pw[i]][seq[i]] = i;
        }
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for(int i = 0; i < p; ++i) {
            for(int j = m; j > 0; --j) {
                int coeff = 1;
                for(int k = 1, z = i; k <= j; ++k, (z += i) >= p && (z -= p)) {
                    coeff = (LL)coeff * (c[i] + k - 1) % mod * inv[k] % mod;
                    if(!coeff)
                        break;
                    for(int x = 0, y = z; x < p; ++x, (++y) == p && (y = 0))
                        if(f[j - k][x])
                            f[j][y] = (f[j][y] + (LL)coeff * f[j - k][x]) % mod;
                }
            }
        }
        int ans = 0;
        for(int i = 0; i <= m; ++i)
            (ans += f[i][0]) >= mod && (ans -= mod);
        printf("%d\n", ans);
    }
    return 0;
}