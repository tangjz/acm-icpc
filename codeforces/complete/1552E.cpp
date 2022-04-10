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
    scanf("%d%d", &n, &m);
    int len = n * m;
    vector<int> col;
    col.reserve(len);
    for(int i = 0; i < len; ++i) {
        int x;
        scanf("%d", &x);
        col.push_back(--x);
    }
    int low = 0, lim = (n - 1) / (m - 1) + 1;
    vector<int> ctr(len);
    vector<queue<int> > pos(n);
    vector<pair<int, int> > ans(n, {-1, -1});
    for(int i = 0; i < len; ++i) {
        if(ans[col[i]].first != -1)
            continue;
        auto &que = pos[col[i]];
        que.push(i);
        while(!que.empty() && que.front() < low)
            que.pop();
        if(que.size() == 2) {
            int L = que.front();
            que.pop();
            int R = que.front();
            que.pop();
            ans[col[i]] = {L, R};
            for(int j = L; j <= R; ++j) {
                ++ctr[j];
                if(ctr[j] == lim)
                    low = max(low, j + 1);
            }
        }
    }
    for(int i = 0; i < n; ++i)
        printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: %d\n", Case, solve());
        solve();
    }
    return 0;
}