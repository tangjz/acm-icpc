#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)1e3 + 9, maxm = (int)1e6 + 9;
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

class PQTree {
private:
    bool failed;
    int n, tot, rt, typ[maxn]; // 0: P, 1: Q
    vector<int> sub[maxn];
    int newNode() {
        typ[++tot] = 0;
        vector<int>().swap(sub[tot]);
        return tot;
    }
    int newP(vector<int> &vec) {
        if(vec.empty())
            return 0;
        if(vec.size() == 1)
            return vec.back();
        int u = newNode();
        sub[u] = vec;
        idx[u] = 0;
        return u;
    }
    void addChild(int u, int v) {
        if(v)
            sub[u].push_back(v);
    }
    void mergeSub(int u, int v) {
        sub[u].insert(sub[u].end(), sub[v].begin(), sub[v].end());
    }

    int sz[maxn], ctr[maxn], idx[maxn];
    int getID(int u) {
        return ctr[u] ? (ctr[u] < sz[u] ? 1 : 2) : 0;
    }
    void dfs(int u, vector<bool> &row) {
        sz[u] = u <= n;
        ctr[u] = u <= n && row[u];
        for(int v: sub[u]) {
            dfs(v, row);
            sz[u] += sz[v];
            ctr[u] += ctr[v];
        }
        idx[u] = ctr[u] ? (ctr[u] < sz[u] ? 1 : 2) : 0;
    }
    int solve(int u, int uid) {
        // printf("solve %d %d\n", u, uid);
        if(failed)
            return 0;
        vector<int> vec[3];
        for(int v: sub[u])
            vec[idx[v]].push_back(v);
        if(vec[1].size() > 2 || (uid > 0 && vec[1].size() > 1)) {
            failed = 1;
            return 0;
        }
        if(!uid && vec[1].size() == 1 && vec[2].empty())
            return solve(vec[1].back(), 0);
        if(!typ[u]) {
            int p2 = newP(vec[2]);
            if(!uid) {
                sub[u] = vec[0];
                if(vec[1].empty()) {
                    addChild(u, p2);
                } else {
                    int p1 = solve(vec[1].front(), 1);
                    addChild(p1, p2);
                    if(vec[1].size() == 2)
                        mergeSub(p1, solve(vec[1].back(), 2));
                    addChild(u, p1);
                }
            } else {
                typ[u] = 1;
                vector<int>().swap(sub[u]);
                addChild(u, newP(vec[0]));
                if(vec[1].size() == 1)
                    mergeSub(u, solve(vec[1].back(), 1));
                addChild(u, p2);
                if(uid == 2)
                    reverse(sub[u].begin(), sub[u].end());
            }
            return u;
        }
        if(idx[sub[u].front()] == 2 || idx[sub[u].back()] == 0)
            reverse(sub[u].begin(), sub[u].end());
        int cnt = 0;
        vector<int> tmp;
        tmp.swap(sub[u]);
        for(int v: tmp)
            if(!idx[v]) {
                addChild(u, v);
                if(cnt == 1)
                    ++cnt;
            } else if(idx[v] == 1) {
                if(cnt > 1) {
                    failed = 1;
                    return 0;
                }
                int p1 = solve(v, ++cnt);
                mergeSub(u, p1);
            } else { // idx[v] == 2
                if(cnt > 1) {
                    failed = 1;
                    return 0;
                }
                if(!cnt)
                    ++cnt;
                addChild(u, v);
            }
        if(uid > 0 && cnt == 2) {
            failed = 1;
            return 0;
        }
        if(uid == 2)
            reverse(sub[u].begin(), sub[u].end());
        return u;
    }

    int calc(int u) {
        if(u <= n)
            return 1;
        int ret = 1, deg = 0;
        for(int v: sub[u]) {
            ret = (LL)ret * calc(v) % mod;
            ++deg;
        }
        if(!typ[u]) {
            for(int i = 2; i <= deg; ++i)
                ret = (LL)ret * i % mod;
        } else if(deg > 1) {
            (ret <<= 1) %= mod;
        }
        return ret;
    }
public:
    void init(int n) {
        tot = failed = 0;
        this -> n = n;
        for(int i = 1; i <= n; ++i)
            newNode();
        rt = newNode();
        for(int i = 1; i <= n; ++i)
            sub[rt].push_back(i);
    }
    bool apply(vector<bool> &row) {
        dfs(rt, row);
        solve(rt, 0);
        return failed;
    }
    int count() {
        return failed ? 0 : calc(rt);
    }
} T;

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    T.init(n);
    for(int i = 0; i < m; ++i) {
        vector<bool> row(n + 1);
        int sz, x;
        scanf("%d", &sz);
        while(sz--) {
            scanf("%d", &x);
            row[x] = 1;
        }
        T.apply(row);
    }
    printf("%d\n", T.count());
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