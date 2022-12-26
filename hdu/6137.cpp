#include <cmath>
#include <cstdio>
#include <algorithm>
typedef double DB;
typedef long long LL;
const int maxs = 7, maxn = 50001, maxLen = 16, maxm = 1 << maxLen | 1;
const DB pi = acos(-1.0); // double is enough
struct complex {
    DB r, i;
    complex() {}
    complex(DB r, DB i) : r(r), i(i) {}
    complex operator + (complex const &t) const { return complex(r + t.r, i + t.i); }
    complex operator - (complex const &t) const { return complex(r - t.r, i - t.i); }
    complex operator * (complex const &t) const { return complex(r * t.r - i * t.i, r * t.i + i * t.r); }
    complex conj() const { return complex(r, -i); }
} w[maxm], B[maxm], C[maxm], D[maxm];
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
int t, n, mod, p[maxs], mx, e[maxs], pp, sz, f[maxn], sp, msk;
LL m;
int main() {
    for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i) {
        int j = i, k = ilim >> 1; // 2 pi / ilim
        for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
        w[i] = complex(cos(pi / k * j), sin(pi / k * j));
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d%I64d", &n, &m);
        mx = 0;
        mod = pp = sz = f[0] = 1;
        for(int i = 0; i < n; ++i) {
            scanf("%d", p + i);
            mod *= p[i];
        }
        for(sp = 1; 1 << (sp << 1) < mod; ++sp);
        msk = (1 << sp) - 1;
        for(int i = 0; i < n; ++i) {
            scanf("%d", e + i);
            mx = std::max(mx, e[i]);
        }
        for(int i = 0; i < n; ++i)
            if(e[i] < mx)
                pp *= p[i];
        int ex = (m - 1) / mx + 1, id = ex * mx - m;
        for(int i = maxLen - 1; i >= 0; --i) {
            if(sz > 1 || f[0] > 1) {
                int len;
                for(len = 1; len < (sz << 1) - 1; len <<= 1);
                for(int i = 0; i < len; ++i)
                    B[i] = i < sz ? complex(f[i] & msk, f[i] >> sp) : complex(0, 0);
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
                sz = (sz << 1) - 1;
                LL rem = 0;
                for(int i = 0; i < sz; ++i) {
                    LL v11 = (LL)(C[i].r + 0.5), v12 = (LL)(C[i].i + 0.5);
                    LL v21 = (LL)(D[i].r + 0.5), v22 = (LL)(D[i].i + 0.5);
                    rem += (((v22 << sp) + v12 + v21) << sp) + v11;
                    f[i] = rem % mod;
                    rem /= mod;
                }
                for( ; rem > 0; rem /= mod)
                    f[sz++] = rem % mod;
            }
            if((ex >> i) & 1) {
                int rem = 0;
                for(int j = 0; j < sz; ++j) {
                    LL tmp = (LL)f[j] * pp + rem;
                    f[j] = tmp % mod;
                    rem = tmp / mod;
                }
                if(rem)
                    f[sz++] = rem;
            }
        }
        printf("%d\n", f[id]);
    }
    return 0;
}
