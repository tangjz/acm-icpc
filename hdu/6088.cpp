#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
typedef double DB;
const int maxn = 100001, maxm = 1 << 18 | 1;
const DB pi = acos(-1.0);
struct complex {
    DB r, i;
    complex() {}
    complex(DB r, DB i) : r(r), i(i) {}
    complex operator + (complex const &t) const { return complex(r + t.r, i + t.i); }
    complex operator - (complex const &t) const { return complex(r - t.r, i - t.i); }
    complex operator * (complex const &t) const { return complex(r * t.r - i * t.i, r * t.i + i * t.r); }
    complex conj() const { return complex(r, -i); }
} w[maxm];
int maxLen, sp, msk;
int tot, pr[maxn], d[maxn], phi[maxn];
int t, n, mod, iact[maxn], m, a[maxn];
void FFT_init() {
    for(maxLen = 1; 1 << maxLen <= n << 1; ++maxLen);
    for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i) {
        int j = i, k = ilim >> 1;
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
        if(i < bitRev[i]) std::swap(a[i], a[bitRev[i]]);
    for(int i = 1, d = 1; d < n; ++i, d <<= 1)
        for(int j = 0; j < n; j += d << 1)
            for(int k = 0; k < d; ++k) {
                complex &AL = a[j + k], &AH = a[j + k + d];
                complex TP = w[k << (maxLen - i)] * AH;
                AH = AL - TP, AL = AL + TP;
            }
    if(flag != -1)
        return;
    std::reverse(a + 1, a + n);
    for(int i = 0; i < n; ++i) {
        a[i].r /= n;
        a[i].i /= n;
    }
}
void polySqr(int aLen, int a[]) {
    static complex B[maxm], C[maxm], D[maxm];
    int len;
    for(len = 1; len < (aLen << 1) - 1; len <<= 1);
    for(int i = 0; i < len; ++i)
        B[i] = i < aLen ? complex(a[i] & msk, a[i] >> sp) : complex(0, 0);
    FFT(len, B, 1);
    complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
    for(int i = 0, j; i < len; ++i) {
        j = (len - i) & (len - 1);
        complex BL = (B[i] + B[j].conj()) * trL;
        complex BH = (B[i] - B[j].conj()) * trH;
        C[i] = BL * (BL + BH * tr);
        D[i] = BH * (BL + BH * tr);
    }
    FFT(len, C, -1);
    FFT(len, D, -1);
    for(int i = 0; i < aLen; ++i) {
        int v11 = (LL)(C[i].r + 0.5) % mod, v12 = (LL)(C[i].i + 0.5) % mod;
        int v21 = (LL)(D[i].r + 0.5) % mod, v22 = (LL)(D[i].i + 0.5) % mod;
        a[i] = (((((LL)v22 << sp) + v12 + v21) << sp) + v11) % mod;
    }
}
int main() {
    phi[1] = 1;
    for(int i = 2; i < maxn; ++i) {
        if(!d[i]) {
            pr[tot++] = d[i] = i;
            phi[i] = i - 1;
        }
        for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
            d[k] = pr[j];
            if(d[i] == pr[j]) {
                phi[k] = phi[i] * pr[j];
                break;
            }
            phi[k] = phi[i] * (pr[j] - 1);
        }
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &mod);
        FFT_init();
        iact[1] = 1;
        for(int i = 2; i <= n; ++i)
            iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
        iact[0] = 1;
        for(int i = 1; i <= n; ++i)
            iact[i] = (LL)iact[i - 1] * iact[i] % mod;
        int ans = 0;
        for(int i = 1; i <= n; ++i) {
            m = 0;
            for(int j = 0; j <= n; j += i)
                a[m++] = iact[j];
            polySqr(m, a);
            int tmp = 0;
            for(int j = i, k = 1; j <= n; j += i, ++k)
                tmp = (tmp + (LL)iact[n - j] * a[k]) % mod;
            ans = (ans + (LL)tmp * phi[i]) % mod;
        }
        for(int i = 1; i <= n; ++i)
            ans = 3LL * i * ans % mod;
        printf("%d\n", ans);
    }
    return 0;
}
