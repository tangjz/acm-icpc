#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
typedef double DB;
const DB pi = acos(-1.0);
const int maxn = 30001, maxLen = 16, maxm = 1 << maxLen | 1;
int phi[maxn], t, n, d, mod, inv[maxn], fact[maxn], iact[maxn];
int F[maxn], G[maxn], A[maxn], B[maxn], C[maxn];
struct complex {
    DB r, i;
    complex() {}
    complex(DB r, DB i) : r(r), i(i) {}
    complex operator + (complex const &t) const { return complex(r + t.r, i + t.i); }
    complex operator - (complex const &t) const { return complex(r - t.r, i - t.i); }
    complex operator * (complex const &t) const { return complex(r * t.r - i * t.i, r * t.i + i * t.r); }
    complex conj() const { return complex(r, -i); }
} w[maxm];
int sp, msk;
void FFT_init() {
    for(int i = 0, iLim = 1 << maxLen; i < iLim; ++i) {
        int j = i, k = iLim >> 1; // 2 pi / iLim
        for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
        w[i] = complex(cos(pi / k * j), sin(pi / k * j));
    }
    for(sp = 1; 1 << (sp << 1) < mod; ++sp);
    msk = (1 << sp) - 1;
}
void FFT(int n, complex a[], int flag) {
    static int bitLen = 0, bitRev[maxm] = {};
    if(n != (1 << bitLen)) {
        for(bitLen = 0; 1 << bitLen < n; ++bitLen);
        for(int i = 1; i < n; ++i)
            bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
    }
    for(int i = 0; i < n; ++i)
        if(i < bitRev[i])
            std::swap(a[i], a[bitRev[i]]);
    for(int i = 1, d = 1; d < n; ++i, d <<= 1)
        for(int j = 0; j < n; j += d << 1)
            for(int k = 0; k < d; ++k) {
                complex &AL = a[j + k], &AH = a[j + k + d];
                complex TP = w[k << (maxLen - i)] * AH;
                AH = AL - TP;
                AL = AL + TP;
            }
    if(flag != -1)
        return;
    std::reverse(a + 1, a + n);
    for(int i = 0; i < n; ++i) {
        a[i].r /= n;
        a[i].i /= n;
    }
}
void poly_conv(int aLen, int a[], int bLen, int b[], int cLen, int c[], bool flag = 0) {
    int len;
    static complex A[maxm], B[maxm], C[maxm], D[maxm];
    if(flag)
        for(len = 1; len < cLen; len <<= 1);
    else
        for(len = 1; len < aLen + bLen - 1; len <<= 1);
    for(int i = 0; i < len; ++i) {
        A[i] = i < aLen ? complex(a[i] & msk, a[i] >> sp) : complex(0, 0);
        B[i] = i < bLen ? complex(b[i] & msk, b[i] >> sp) : complex(0, 0);
    }
    FFT(len, A, 1);
    FFT(len, B, 1);
    complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
    for(int i = 0; i < len; ++i) {
        int j = (len - i) & (len - 1);
        complex AL = (A[i] + A[j].conj()) * trL;
        complex AH = (A[i] - A[j].conj()) * trH;
        complex BL = (B[i] + B[j].conj()) * trL;
        complex BH = (B[i] - B[j].conj()) * trH;
        C[i] = AL * (BL + BH * tr);
        D[i] = AH * (BL + BH * tr);
    }
    FFT(len, C, -1);
    FFT(len, D, -1);
    for(int i = 0; i < cLen; ++i) {
        int v11 = (LL)(C[i].r + 0.5) % mod, v12 = (LL)(C[i].i + 0.5) % mod;
        int v21 = (LL)(D[i].r + 0.5) % mod, v22 = (LL)(D[i].i + 0.5) % mod;
        c[i] = (((((LL)v22 << sp) + v12 + v21) << sp) + v11) % mod;
    }
}
inline void poly_inv(int n, int f[], int g[]) {
    if(n == 1) {
        g[0] = 1;
        return;
    }
    int half = (n + 1) >> 1;
    poly_inv(half, f, g);
    static int h[maxn];
    poly_conv(n, f, half, g, n, h);
    poly_conv(half, g, n - half, h + half, n - half, g + half);
    for(int i = half; i < n; ++i)
        g[i] = g[i] ? mod - g[i] : 0;
}
// A[i] * B[j] -> (i + j) d G[i + j] (i, j <= n / d)
void cdq(int L, int R) {
    if(L == R) {
        B[L] = L ? (LL)B[L] * inv[L * d] % mod : 1;
        return;
    }
    int M = (L + R) >> 1;
    cdq(L, M);
    int len;
    for(len = 1; len < R - L + 1; len <<= 1);
    poly_conv(M - L + 1, B + L, R - L + 1, A, R - L + 1, C, 1);
    for(int i = M + 1, *_C = C - L; i <= R; ++i)
        if((B[i] += _C[i]) >= mod)
            B[i] -= mod;
    cdq(M + 1, R);
}
int mod_pow(int x, LL k) {
    int ret = 1;
    for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
        (k & 1) && (ret = (LL)ret * x % mod);
    return ret;
}
int main() {
    for(int i = 1; i < maxn; ++i) {
        phi[i] += i;
        for(int j = i + i; j < maxn; j += i)
            phi[j] -= phi[i];
    }
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d", &n, &mod);
        inv[1] = 1;
        for(int i = 2; i <= n; ++i)
            inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
        fact[0] = iact[0] = 1;
        for(int i = 1; i <= n; ++i) {
            fact[i] = (LL)fact[i - 1] * i % mod;
            iact[i] = (LL)iact[i - 1] * inv[i] % mod;
        }
        FFT_init();
        G[0] = 1;
        A[0] = 0; // A = xG'
        for(int i = 1; i <= n; ++i) {
            G[i] = (LL)mod_pow(2, (i * (i - 1LL)) >> 1) * iact[i] % mod;
            A[i] = (LL)G[i] * i % mod;
        }
        poly_inv(n + 1, G, B); // B = G^-1
        poly_conv(n + 1, A, n + 1, B, n + 1, F); // xF' = xG' * G^-1
        int ans = G[n];
        for(d = 2; d <= n; ++d) {
            if(n % d > 0)
                continue;
            for(int i = 0, j = 0; i <= n; i += d, ++j) {
                A[j] = F[i];
                B[j] = 0;
            }
            cdq(0, n / d);
            ans = (ans + (LL)phi[d] * B[n / d]) % mod;
        }
        ans = (LL)ans * fact[n] % mod;
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
