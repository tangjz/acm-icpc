#include <bits/stdc++.h>
using namespace std;
typedef double DB;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxLen = 18, maxm = 1 << maxLen | 1, mod = (int)1e9 + 7, sp = 15, msk = 32767;
const DB pi = acos(-1.0);
struct Complex {
    DB r, i;
    Complex(DB r = 0, DB i = 0) : r(r), i(i) {}
    Complex operator + (Complex const &t) const {
        return (Complex){r + t.r, i + t.i};
    }
    Complex operator - (Complex const &t) const {
        return (Complex){r - t.r, i - t.i};
    }
    Complex operator * (Complex const &t) const {
        return (Complex){r * t.r - i * t.i, r * t.i + i * t.r};
    }
    Complex conj() const {
        return (Complex){r, -i};
    }
} w[maxm];
void FFT(int n, Complex a[], int flag) {
    static int bitLen = 0, bitRev[maxm] = {};
    if(n != 1 << bitLen) {
        for(bitLen = 0; 1 << bitLen < n; ++bitLen);
        for(int i = 1; i < n; ++i)
            bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
    }
    for(int i = 1; i < n; ++i)
        if(i < bitRev[i])
            swap(a[i], a[bitRev[i]]);
    for(int i = 1, d = 1; d < n; ++i, d <<= 1)
        for(int j = 0; j < n; j += d << 1)
            for(int k = 0; k < d; ++k) {
                Complex &AL = a[j + k], &AH = a[j + k + d], TP = w[k << (maxLen - i)] * AH;
                AH = AL - TP;
                AL = AL + TP;
            }
    if(flag == -1) {
        reverse(a + 1, a + n);
        for(int i = 0; i < n; ++i) {
            a[i].r /= n;
            a[i].i /= n;
        }
    }
}
void polyMul(int aLen, int a[], int bLen, int b[], int c[]) {
    static Complex A[maxm], B[maxm], C[maxm], D[maxm];
    int cLen = aLen + bLen - 1, len;
    for(len = 1; len < cLen; len <<= 1);
    for(int i = 0; i < len; ++i) {
        A[i] = i < aLen ? Complex(a[i] & msk, a[i] >> sp) : Complex(0, 0);
        B[i] = i < bLen ? Complex(b[i] & msk, b[i] >> sp) : Complex(0, 0);
    }
    FFT(len, A, 1);
    FFT(len, B, 1);
    Complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
    for(int i = 0; i < len; ++i) {
        int j = i ? len - i : 0;
        Complex AL = (A[i] + A[j].conj()) * trL;
        Complex AH = (A[i] - A[j].conj()) * trH;
        Complex BL = (B[i] + B[j].conj()) * trL;
        Complex BH = (B[i] - B[j].conj()) * trH;
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
int t, n, a[maxn], f[maxn], g[maxn << 1 | 1], h[maxn << 1 | 1];
LL m;
inline pair<int, LL> calc(LL x, LL y) {
    pair<int, LL> ret = make_pair(1, 0LL);
    for( ; x > y; --x) {
        LL tp = x;
        for( ; tp % mod == 0; tp /= mod, ++ret.second);
        tp %= mod;
        ret.first = (LL)ret.first * tp % mod;
    }
    return ret;
}
inline int mod_sqr(LL x) {
    x %= mod;
    return x * x % mod;
}
inline int mod_inv(int x) {
    return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main() {
    for(int i = 0, iLim = 1 << maxLen; i < iLim; ++i) {
        int j = i << 1, k = iLim;
        for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
        w[i] = Complex(cos(pi / k * j), sin(pi / k * j));
    }
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        int mx = 0, ans = 0;
        scanf("%d%lld", &n, &m);
        --m;
        for(int i = 0; i < n; ++i) {
            scanf("%d", a + i);
            m -= a[i] << 1;
            mx = max(mx, a[i]);
        }
        memset(h, 0, (mx << 1 | 1) * sizeof(int));
        for(int i = 0; i < n; ++i) {
            ++h[2];
            h[a[i] + 2] -= 2;
            ++h[(a[i] + 1) << 1];
        }
        for(int i = 0; i <= mx << 1; ++i)
            (h[i] = (h[i] + (i > 0 ? 2LL * h[i - 1] : 0LL) + (i > 1 ? -h[i - 2] : 0)) % mod) < 0 && (h[i] += mod);
        memset(f, 0, (mx + 1) * sizeof(int));
        for(int i = 0; i < n; ++i)
            ++f[a[i]];
        for(int i = mx - 1; i >= 1; --i)
            (f[i] += f[i + 1]) >= mod && (f[i] -= mod);
        polyMul(mx + 1, f, mx + 1, f, g);
        for(int i = 0; i <= mx << 1; ++i)
            (g[i] -= h[i]) >= mod && (g[i] += mod);
        if(m > 0) {
            pair<int, LL> ways = calc(m + n, m);
            if(!ways.second)
                ans = (ans + (LL)ways.first * mod_sqr(m)) % mod;
        }
        if(m + mx > 0) {
            int low = max(-m, 1LL);
            pair<int, LL> ways = calc(m + low + n - 1, m + low);
            for(int i = low; i <= mx; ++i) {
                if(m + i > 0 && f[i] && !ways.second)
                    ans = (ans + 2LL * ways.first * mod_sqr(m + i) % mod * f[i]) % mod;
                LL tp = m + i + n;
                for( ; tp % mod == 0; tp /= mod, ++ways.second);
                tp %= mod;
                ways.first = (LL)ways.first * tp % mod;
                tp = m + i + 1;
                for( ; tp % mod == 0; tp /= mod, --ways.second);
                tp %= mod;
                ways.first = (LL)ways.first * mod_inv(tp) % mod;
            }
        }
        if(n > 1 && m + (mx << 1) > 0) {
            int low = max(-m, 2LL);
            pair<int, LL> ways = calc(m + low + n - 2, m + low);
            for(int i = low; i <= mx << 1; ++i) {
                if(m + i > 0 && g[i] && !ways.second)
                    ans = (ans + (LL)ways.first * mod_sqr(m + i) % mod * g[i]) % mod;
                LL tp = m + i + n - 1;
                for( ; tp % mod == 0; tp /= mod, ++ways.second);
                tp %= mod;
                ways.first = (LL)ways.first * tp % mod;
                tp = m + i + 1;
                for( ; tp % mod == 0; tp /= mod, --ways.second);
                tp %= mod;
                ways.first = (LL)ways.first * mod_inv(tp) % mod;
            }
        }
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
