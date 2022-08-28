#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    int n, m, st = 0;
    if(scanf("%d%d", &n, &m) != 2) {
        puts("0");
        return 0;
    }
    assert(n > 0 && m > 0);
    vector<int> match(m, -1), vis(m);
    vector<pair<int, vector<int> > > workers;
    workers.reserve(n);
    while(n--) {
        int a, b, c;
        if(scanf("%d%d%d", &a, &b, &c) != 3)
            continue;
        assert(1 <= a && a < b && b <= m && c > 0);
        workers.push_back({c, {--a, --b}});
    }
    LL ans = 0;
    sort(workers.begin(), workers.end());
    function<bool(int)> path = [&](int u) {
        for(int v: workers[u].second) {
            if(vis[v] == st)
                continue;
            vis[v] = st;
            if(match[v] == -1 || path(match[v])) {
                match[v] = u;
                return 1;
            }
        }
        return 0;
    };
    for(int i = workers.size() - 1; i >= 0; --i) {
        ++st;
        if(path(i))
            ans += workers[i].first;
    }
    printf("%lld\n", ans);
    return 0;
}
