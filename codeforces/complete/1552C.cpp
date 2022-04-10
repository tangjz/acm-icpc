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

void solve() {
    int n, m;
    static bool vis[maxn];
    static pair<int, int> a[maxn];

    scanf("%d%d", &n, &m);
    memset(vis, 0, (n + n) * sizeof(bool));
    for(int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x;
        --y;
        if(x > y)
            swap(x, y);
        a[i] = {x, y};
        vis[x] = vis[y] = 1;
    }
    vector<int> rem;
    for(int i = 0; i < n + n; ++i)
        if(!vis[i])
            rem.push_back(i);
    int half = (int)rem.size() / 2;
    for(int i = 0; i < n - m; ++i)
        a[m + i] = {rem[i], rem[half + i]};
    int ans = 0;
    sort(a, a + n);
    for(int i = 0; i < n; ++i) {
        // printf("#%d: %d %d\n", i, a[i].first + 1, a[i].second + 1);
        for(int j = i + 1; j < n; ++j) {
            bool lft = a[i].first < a[j].first && a[j].first < a[i].second;
            bool rht = a[i].first < a[j].second && a[j].second < a[i].second;
            ans += lft != rht;
        }
    }
    printf("%d\n", ans);
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