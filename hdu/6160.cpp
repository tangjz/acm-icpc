#include <cstdio>
#include <cstring>
typedef unsigned UL;
typedef unsigned long long ULL;
const int maxn = 10 * 56 * 56 + 1, maxm = 64 * 11 * 11 + 1, maxs = 10 * 64 * 45 * 45 + 1, maxd = 1 << 16 | 1;
int n, m, c, ih, iw, kh, kw, sh, sw, oh, ow, bits[maxd];
ULL in[maxn], ker[maxm];
inline int popcount(UL x) {
    return bits[x >> 16] + bits[x & 65535];
}
inline int popcount(ULL x) {
    return popcount((UL)(x >> 32)) + popcount((UL)x);
}
int main() {
    for(int i = 1; i < maxd; ++i)
        bits[i] = bits[i >> 1] + (i & 1);
    while(scanf("%d%d%d%d", &n, &c, &ih, &iw) == 4) {
        memset(in, 0, n * ih * iw * sizeof(ULL));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < c; ++j)
                for(int x = 0, idx = i * ih * iw; x < ih; ++x)
                    for(int y = 0; y < iw; ++y, ++idx) {
                        int v;
                        scanf("%d", &v);
                        in[idx] |= (ULL)(v == -1) << j;
                    }
        scanf("%d%*d%d%d", &m, &kh, &kw);
        memset(ker, 0, m * kh * kw * sizeof(ULL));
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < c; ++j)
                for(int x = 0, kdx = i * kh * kw; x < kh; ++x)
                    for(int y = 0; y < kw; ++y, ++kdx) {
                        int v;
                        scanf("%d", &v);
                        ker[kdx] |= (ULL)(v == -1) << j;
                    }
        scanf("%d%d", &sh, &sw);
        oh = (ih - kh) / sh + 1;
        ow = (iw - kw) / sw + 1;
        int ans = 0;
        for(int i = 0, odx = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                for(int x = 0; x < oh; ++x)
                    for(int y = 0; y < ow; ++y, ++odx) {
                        int ctr = c * kh * kw;
                        for(int kx = 0, ix = x * sh + kx, kdx = j * kh * kw; kx < kh; ++kx, ++ix)
                            for(int ky = 0, iy = y * sw + ky, idx = (i * ih + ix) * iw + iy; ky < kw; ++ky, ++iy, ++idx, ++kdx)
                                ctr -= popcount(in[idx] ^ ker[kdx]) << 1;
                        ans += odx * ctr;
                    }
        printf("%d %d %d %d\n%u\n", n, m, oh, ow, ans);
    }
    return 0;
}
