#include <bits/stdc++.h>
using namespace std;

void solve() {
    vector<vector<double> > que;
    auto det = [&](double x0, double y0, double x1, double y1, double x2, double y2) -> double {
        return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
    };
    auto sgn = [&](double x) -> int {
        return (x > 0) - (x < 0);
    };
    auto hasIntersection = [&](vector<double> const &lft, vector<double> const &rht) {
        int c1 = sgn(det(lft[0], lft[1], lft[2], lft[3], rht[0], rht[1]));
        int c2 = sgn(det(lft[0], lft[1], lft[2], lft[3], rht[2], rht[3]));
        int c3 = sgn(det(rht[0], rht[1], rht[2], rht[3], lft[0], lft[1]));
        int c4 = sgn(det(rht[0], rht[1], rht[2], rht[3], lft[2], lft[3]));
        return c1 * c2 <= 0 && c3 * c4 <= 0;
    };
    vector<int> dsu;
    function<int(int)> dsuFind = [&](int x) {
        return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
    };
    auto dsuMerge = [&](int u, int v) {
        u = dsuFind(u);
        v = dsuFind(v);
        if(u == v)
            return;
        if(dsu[u] < dsu[v])
            swap(u, v);
        dsu[v] += dsu[u];
        dsu[u] = v;
    };
    int T;
    scanf("%d", &T);
    vector<double> vals(4);
    while(T--) {
        static char op[2];
        scanf("%s", op);
        if(op[0] == 'Q') {
            int idx;
            scanf("%d", &idx);
            printf("%d\n", -dsu[dsuFind(--idx)]);
            continue;
        }
        for(int i = 0; i < 4; ++i)
            scanf("%lf", &vals[i]);
        que.push_back(vals);
        dsu.push_back(-1);
        for(int i = que.size() - 2; i >= 0; --i)
            if(dsuFind(i) != dsuFind(que.size() - 1) && hasIntersection(que[i], que.back()))
                dsuMerge(i, que.size() - 1);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        if(Case > 1)
            puts("");
        solve();
    }
    return 0;
}
