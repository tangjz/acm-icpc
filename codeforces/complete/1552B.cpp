#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)2e5 + 9, maxm = (int)1e6 + 9;
const int maxc = 26, maxd = 10;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = (LL)INF << 32 | INF;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
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
inline LL mod_mul(LL x, LL y, LL mod) {
    LL ret = x * y - (LL)((LD)x * y / mod + 1e-3) * mod;
    for( ; ret < 0; ret += mod);
    return ret;
}
inline LL mod_pow(LL x, LL k, LL mod) {
    LL ret = mod > 1 ? 1 : 0;
    for( ; k > 0; k >>= 1, x = mod_mul(x, x, mod))
        if(k & 1)
            ret = mod_mul(ret, x, mod);
    return ret;
}

const int maxv = 5, maxt = 11;
int tot;
vector<int> pos[maxv];
void solve() {
    int n;
    static int rk[maxv][maxn];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < maxv; ++j)
            scanf("%d", rk[j] + i);
    int best = 0;
    auto cmp = [&](int u, int v) {
        int cnt = 0;
        for(int i = 0; i < maxv; ++i)
            cnt += rk[i][u] < rk[i][v];
        return cnt >= 3;
    };
    for(int i = 1; i < n; ++i)
        if(cmp(i, best))
            best = i;
    for(int i = 0; i < n; ++i)
        if(i != best && cmp(i, best)) {
            puts("-1");
            return;
        }
    printf("%d\n", best + 1);
}

int main() {
    for(int i = 0; i < maxv; ++i)
        for(int j = i + 1; j < maxv; ++j)
            for(int k = j + 1; k < maxv; ++k) {
                pos[i].push_back(tot);
                pos[j].push_back(tot);
                pos[k].push_back(tot);
                ++tot;
            }
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: %d\n", Case, solve());
        solve();
    }
    return 0;
}