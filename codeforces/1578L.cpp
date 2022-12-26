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

const int maxn = (int)1e6 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const i64 INF64 = (i64)INF << 32 | INF;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}


int n, m, tot;
int c[maxn];
int dsu[maxn], idx[maxn], upp[maxn];
vector<int> e[maxn];
i64 sz[maxn], adt, ans;
int dsuFind(int x) {
    return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
}
pair<i64, i64> dfs(int u) {
    if(u < n) {
        return {INF64, (i64)c[u]};
    }
    vector<pair<i64, i64> > seq;
    for(int v: e[u]) {
        // printf("%d -> %d\n", u, v);
        seq.push_back(dfs(v));
    }
    sort(seq.begin(), seq.end(), [&](pair<i64, i64> const &p, pair<i64, i64> const &q) {
        i64 lft = min(p.first, p.second + min(q.first, (i64)upp[u]));
        i64 rht = min(q.first, q.second + min(p.first, (i64)upp[u]));
        return lft > rht;
    });
    pair<i64, i64> ret = {INF64, 0LL};
    bool fir = 1;
    for(auto &it: seq) {
        ret.first = min(ret.first, fir ? it.first : ret.second + min(it.first, (i64)upp[u]));
        ret.second += it.second;
        fir = 0;
    }
    // printf("%d: %lld %lld\n", u, ret.first, ret.second);
    return ret;
}
void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        scanf("%d", c + i);
    }
    typedef struct { int u, v, w; } Edge;
    static Edge edges[maxn];
    for(int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edges[i] = (Edge){--u, --v, w};
    }
    sort(edges, edges + m, [&](Edge const &p, Edge const &q) {
        return p.w > q.w;
    });
    tot = n;
    for(int i = 0; i < n; ++i) {
        idx[i] = i;
        dsu[i] = -1;
        sz[i] = c[i];
        upp[i] = INF;
    }
    for(int i = 0, j; i < m; i = j) {
        map<int, set<int> > sp;
        for(j = i; j < m && edges[i].w == edges[j].w; ++j) {
            int u = dsuFind(edges[j].u);
            int v = dsuFind(edges[j].v);
            if(u == v)
                continue;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            sp[u].insert(idx[u]);
            sp[v].insert(idx[v]);
            if(sp[u].size() > sp[v].size())
                sp[u].swap(sp[v]);
            for(int x: sp[u])
                sp[v].insert(x);
            sp.erase(u);
            break;
        }
        for(auto &it: sp) {
            int u = it.first;
            int rt = tot++;
            idx[u] = rt;
            upp[rt] = edges[i].w;
            sz[rt] = 0;
            for(int x: it.second) {
                sz[rt] += sz[x];
                e[rt].push_back(x);
            }
            sort(e[rt].begin(), e[rt].end(), [&](int const &p, int const &q) {
                return sz[p] < sz[q];
            });
        }
    }
    pair<i64, i64> res = dfs(tot - 1);
    i64 ans = res.first - res.second;
    printf("%lld\n", ans > 0 ? ans : -1LL);
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
