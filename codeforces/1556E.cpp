#include <bits/stdc++.h>
using namespace std;

typedef signed i32;
typedef unsigned u32;
typedef long long i64;
typedef unsigned long long u64;
// typedef __int128_t i128;
// typedef __uint128_t u128;
typedef float f32;
typedef double f64;
typedef long double f128;

const int maxn = (int)1e5 + 1, maxm = (int)2e6 + 1;
const int maxd = 10, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const i64 INFLL = (i64)INF << 32 | INF;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}
inline bool is_prime(int x) {
    if(x <= 2 || !(x & 1))
        return x == 2;
    for(int i = 3; i * i <= x; i += 2)
        if(x % i == 0)
            return 0;
    return 1;
}
inline i64 mod_mul(i64 x, i64 y, i64 mod) {
    i64 ret = x * y - (i64)((f128)x * y / mod + 1e-3) * mod;
    for( ; ret < 0; ret += mod);
    return ret;
}
inline i64 mod_pow(i64 x, i64 k, i64 mod) {
    i64 ret = mod > 1 ? 1 : 0;
    for( ; k > 0; k >>= 1, x = mod_mul(x, x, mod))
        if(k & 1)
            ret = mod_mul(ret, x, mod);
    return ret;
}

typedef pair<i64, i64> Segment;

inline int seg_idx(int L, int R) {
    return (L + R) | (L < R);
}

void seg_init(Segment seg[], int L, int R, i64 a[]) {
    int rt = seg_idx(L, R);
    if(L < R) {
        int M = (L + R) >> 1;
        seg_init(seg, L, M, a);
        seg_init(seg, M + 1, R, a);
        int lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
        seg[rt] = {min(seg[lch].first, seg[rch].first), max(seg[lch].second, seg[rch].second)};
    } else {
        seg[rt] = {a[L], a[R]};
    }
}

Segment seg_que(Segment seg[], int L, int R, int l, int r) {
    if(l <= L && R <= r)
        return seg[seg_idx(L, R)];
    int M = (L + R) >> 1;
    if(r <= M)
        return seg_que(seg, L, M, l, r);
    if(l > M)
        return seg_que(seg, M + 1, R, l, r);
    Segment lft = seg_que(seg, L, M, l, r);
    Segment rht = seg_que(seg, M + 1, R, l, r);
    return {min(lft.first, rht.first), max(lft.second, rht.second)};
}

void solve() {
    int n, q;
    static i64 a[maxn];
    static Segment seg[maxn << 1 | 1];
    scanf("%d%d", &n, &q);
    a[0] = 0;
    for(int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    for(int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        a[i] -= x;
        a[i] += a[i - 1];
    }
    seg_init(seg, 1, n, a);
    while(q--) {
        int L, R;
        scanf("%d%d", &L, &R);
        if(a[L - 1] != a[R]) {
            puts("-1");
            continue;
        }
        Segment ret = seg_que(seg, 1, n, L, R - 1);
        ret.first -= a[L - 1];
        ret.second -= a[L - 1];
        printf("%lld\n", ret.second > 0 ? -1LL : -ret.first);
    }
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}