#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)2e5 + 9, maxm = (int)1e6 + 9;
const int maxc = 26, maxd = 10;
const int mod = 998244353, INF = 0x3f3f3f3f;
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

void solve() {
    int n;
    scanf("%d", &n);
    vector<vector<int> > e(n);
    for(int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u;
        --v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    vector<int> p(n, -1), ord = {0};
    for(int i = 0; i < (int)ord.size(); ++i) {
        int u = ord[i];
        for(int v: e[u]) {
            if(v == p[u])
                continue;
            p[v] = u;
            ord.push_back(v);
        }
    }
    reverse(ord.begin(), ord.end());
    vector<int> ans(n + 1), adt(n);
    ans[1] = 1;
    for(int i = n; i >= 2; --i) {
        (ans[1] <<= 1) %= mod;
        if((n - 1) % i > 0)
            continue;
        bool ban = 0;
        for(int j = i + i; j <= n; j += i)
            ban |= ans[j];
        if(ban)
            continue;
        for(int u: ord) {
            int cnt = 0;
            for(int v: e[u])
                if(v != p[u])
                    cnt += adt[v];
            if(cnt % i == 0) {
                adt[u] = 1;
            } else if((cnt + 1) % i == 0) {
                adt[u] = 0;
            } else {
                ban = 1;
                break;
            }
        }
        ban |= !adt[0];
        if(!ban)
            ++ans[i];
    }
    for(int i = 2; i <= n; ++i)
        ans[1] -= ans[i];
    if(ans[1] < 0)
        ans[1] += mod;
    for(int i = 1; i <= n; ++i)
        printf("%d%c", ans[i], " \n"[i == n]);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: %d\n", Case, solve());
        solve();
    }
    return 0;
}