#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 166667, maxm = 6001, mod = (int)1e9 + 7;
int t, n, m, a[maxn], tot, c[maxm], w[maxm], f[maxn];
inline void mod_inc_mul(int &x, int y, int z) {
    x = (x + (LL)y * z) % mod;
}
struct Poly {
    int deg, term[maxm << 1 | 1];
    Poly operator * (Poly const &t) const {
        Poly ret = (Poly){deg + t.deg};
        for(int i = 0; i <= deg; ++i) if(term[i])
            for(int j = 0; j <= t.deg; ++j) if(t.term[j])
                mod_inc_mul(ret.term[i + j], term[i], t.term[j]);
        return ret;
    }
    Poly operator % (Poly const &t) const {
        Poly ret = *this;
        for(int i = ret.deg; i >= t.deg; --i) {
            if(!ret.term[i])
                continue;
            int coeff = mod - ret.term[i]; // t.term[t.deg] = 1
            for(int j = 0; j <= t.deg; ++j)
                mod_inc_mul(ret.term[i - j], coeff, t.term[t.deg - j]);
        }
        for( ; ret.deg > 0 && !ret.term[ret.deg]; --ret.deg);
        return ret;
    }
} A, B, M;
int main() {
    a[0] = 1;
    for(int i = 1; i < maxn; ++i)
        (a[i] = a[i - 1] << 1) >= mod && (a[i] -= mod);
    a[1] = 1;
    a[2] = 2;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        tot = 0;
        for(int i = 1; i * i <= m; ++i) {
            if(m % i > 0)
                continue;
            int j = m / i;
            if(i <= n && (j & 1)) {
                c[tot] = i;
                w[tot++] = a[i];
            }
            if(i < j && j <= n && (i & 1)) {
                c[tot] = j;
                w[tot++] = a[j];
            }
        }
        if(n >= 4 && (m & 3) == 2) {
            c[tot] = 4;
            w[tot++] = a[2] << 1;
            m == 2 && (m = 4);
        }
        if(m < maxm) {
            M.deg = m;
            M.term[m] = 1;
            memset(M.term, 0, m * sizeof(int));
            for(int i = 0; i < tot; ++i)
                (M.term[m - c[i]] -= w[i]) < 0 && (M.term[m - c[i]] += mod);
            A = (Poly){0, 1};
            B = (Poly){1, 0, 1};
            for(n += m - 1; n > 0; n >>= 1, B = B * B % M)
                if(n & 1)
                    A = A * B % M;
            printf("%d\n", A.deg == m - 1 ? A.term[m - 1] : 0);
        } else {
            f[0] = 1;
            memset(f + 1, 0, n * sizeof(int));
            for(int i = 1; i <= n; ++i)
                for(int j = 0; j < tot; ++j)
                    if(i >= c[j])
                        mod_inc_mul(f[i], f[i - c[j]], w[j]);
            printf("%d\n", f[n]);
        }
    }
    return 0;
}