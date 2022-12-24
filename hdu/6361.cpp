#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef complex<double> Complex;
const int maxLen = 16, maxm = 1 << maxLen | 1, mod = (int)1e9 + 7, SP = 15, MSK = 32767, SD = 73741817; // (1 << (SP + SP)) % mod
const double pi = acos(-1.0);
int f[maxm], g[maxm];
Complex w[maxm], A[maxm], B[maxm], C[maxm], D[maxm];
inline void FFT(int n, Complex a[], int flag) { // dft(a) or idft(a) * n
    static int bitLen = 0, bitRev[maxm] = {};
    if(n != (1 << bitLen)) {
        for(bitLen = 0; 1 << bitLen < n; ++bitLen);
        for(int i = 1; i < n; ++i)
            bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
    }
    for(int i = 0; i < n; ++i)
        if(i < bitRev[i])
            swap(a[i], a[bitRev[i]]);
    for(int i = 1, d = 1; d < n; ++i, d <<= 1)
        for(int j = 0; j < n; j += d << 1)
            for(int k = 0; k < d; ++k) {
                Complex &AL = a[j + k], &AH = a[j + k + d];
                Complex TP = w[k << (maxLen - i)] * AH;
                AH = AL - TP;
                AL = AL + TP;
            }
    if(flag == -1)
        reverse(a + 1, a + n);
}
inline void cyc_conv(int len, int a[], int b[]) { // a = a * b
    for(int i = 0; i < len; ++i) {
        A[i] = Complex(a[i] & MSK, a[i] >> SP);
        B[i] = Complex(b[i] & MSK, b[i] >> SP);
    }
    FFT(len, A, 1);
    FFT(len, B, 1);
    Complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
    for(int i = 0; i < len; ++i) {
        int j = (len - i) & (len - 1);
        Complex AL = (A[i] + conj(A[j])) * trL;
        Complex AH = (A[i] - conj(A[j])) * trH;
        Complex BL = (B[i] + conj(B[j])) * trL;
        Complex BH = (B[i] - conj(B[j])) * trH;
        C[i] = AL * (BL + BH * tr);
        D[i] = AH * (BL + BH * tr);
    }
    FFT(len, C, -1);
    FFT(len, D, -1);
    for(int i = 0; i < len; ++i) {
        int v11 = (LL)(C[i].real() / len + 0.5) % mod;
        int v12 = (LL)(C[i].imag() / len + 0.5) % mod;
        int v21 = (LL)(D[i].real() / len + 0.5) % mod;
        int v22 = (LL)(D[i].imag() / len + 0.5) % mod;
        a[i] = (v11 + ((LL)(v12 + v21) << SP) + (LL)v22 * SD) % mod;
    }
}
const int maxn = (int)6e4 + 1;
int inv[maxn], a[maxn], b[maxn], c[maxn], d[maxn], a2[maxn], b2[maxn], d2[maxn];
int da2[maxn], db[maxn], db2[maxn], dc[maxn], dd[maxn], dd2[maxn];
int sa2[maxn], sb[maxn], sb2[maxn], sc[maxn], sd[maxn], sd2[maxn], ans[maxn];
inline int mod_add(int x, int y) {
    return (x += y) < mod ? x : x - mod;
}
inline int mod_sub(int x, int y) {
    return (x -= y) < 0 ? x + mod : x;
}
inline void solve(int L, int R) {
    if(L == R) {
        if(L == 1)
            return;
        int ivs = inv[L] = mod - (int)(mod / L * (LL)inv[mod % L] % mod);
        sa2[L] = (LL)sa2[L] * ivs % mod;
        sb[L] = (LL)sb[L] * ivs % mod;
        sb2[L] = (LL)sb2[L] * ivs % mod;
        sc[L] = (LL)sc[L] * ivs % mod;
        sd[L] = (LL)sd[L] * ivs % mod;
        sd2[L] = (LL)sd2[L] * ivs % mod;
        a[L] = mod_sub(sb2[L], sb[L]);
        b[L] = (LL)sa2[L] * inv[2] % mod;
        c[L] = mod_sub(sd2[L], sd[L]);
        d[L] = sc[L];
        a2[L] = mod_add(a[L], a[L]);
        b2[L] = mod_add(b[L], b[L]);
        d2[L] = mod_add(d[L], d[L]);
        da2[L] = (LL)L * a2[L] % mod;
        db[L] = (LL)L * b[L] % mod;
        db2[L] = (LL)L * b2[L] % mod;
        dc[L] = (LL)L * c[L] % mod;
        dd[L] = (LL)L * d[L] % mod;
        dd2[L] = (LL)L * d2[L] % mod;
        return;
    }
    int M = (L + R) >> 1;
    solve(L, M);
    int len;
    for(len = 1; len < R - L + 1; len <<= 1);
    if(R < L + L) {
        auto proc = [&](int a[], int da[], int sa[]) {
            for(int i = 0, j = L; i < len; ++i, ++j) {
                f[i] = j <= M ? da[j] : 0;
                g[i] = j <= R ? mod_add(a[i], sa[i]) : 0;
            }
            cyc_conv(len, f, g);
            for(int i = M + 1, j = M + 1 - L; i <= R; ++i, ++j)
                sa[i] = mod_add(sa[i], f[j]);
            for(int i = 0, j = L; i < len; ++i, ++j) {
                f[i] = j <= R ? da[i] : 0;
                g[i] = j <= M ? mod_add(a[j], sa[j]) : 0;
            }
            cyc_conv(len, f, g);
            for(int i = M + 1, j = M + 1 - L; i <= R; ++i, ++j)
                sa[i] = mod_add(sa[i], f[j]);
        };
        proc(a2, da2, sa2);
        proc(b, db, sb);
        proc(b2, db2, sb2);
        proc(c, dc, sc);
        proc(d, dd, sd);
        proc(d2, dd2, sd2);
    } else {
        int low = max(M + 1, L + L), upp = min(R, M + M);
        auto proc = [&](int a[], int da[], int sa[]) {
            for(int i = 0, j = L; i < len; ++i, ++j) {
                f[i] = j <= M ? da[j] : 0;
                g[i] = j <= M ? mod_add(a[j], sa[j]) : 0;
            }
            cyc_conv(len, f, g);
            for(int i = low, j = low - L - L; i <= upp; ++i, ++j)
                sa[i] = mod_add(sa[i], f[j]);
        };
        proc(a2, da2, sa2);
        proc(b, db, sb);
        proc(b2, db2, sb2);
        proc(c, dc, sc);
        proc(d, dd, sd);
        proc(d2, dd2, sd2);
    }
    solve(M + 1, R);
}
int main() {
    inv[1] = a[1] = b[1] = c[1] = d[1] = db[1] = dc[1] = dd[1] = ans[1] = 1;
    a2[1] = b2[1] = d2[1] = da2[1] = db2[1] = dd2[1] = 2;
    for(int i = 0, iLim = 1 << maxLen; i < iLim; ++i) {
        int j = i, k = iLim >> 1; // 2 pi / iLim
        for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
        w[i] = Complex(cos(pi / k * j), sin(pi / k * j));
    }
    solve(1, maxn - 1);
    for(int i = 2, prd = 1; i < maxn; ++i) {
        prd = (LL)prd * i % mod;
        (ans[i] = ((LL)a2[i] + b2[i] - c[i] - d[i]) * prd % mod) < 0 && (ans[i] += mod);
    }
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        printf("%d\n", ans[n]);
    }
    return 0;
}