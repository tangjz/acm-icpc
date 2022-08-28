#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> dsu(n, -1);
    function<int(int)> dsuFind = [&](int u) -> int {
        return dsu[u] < 0 ? u : (dsu[u] = dsuFind(dsu[u]));
    };
    auto dsuMerge = [&](int u, int v) -> bool {
        u = dsuFind(u);
        v = dsuFind(v);
        if(u == v)
            return 0;
        if(dsu[u] < dsu[v])
            swap(u, v);
        dsu[u] += dsu[v];
        dsu[v] = u;
        return 1;
    };
    int rem = n;
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        rem -= !dsuMerge(--u, --v) && -dsu[dsuFind(u)] & 1;
    }
    printf("%d\n", rem - (rem & 1));
    return 0;
}
