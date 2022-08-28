#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, p, q;
    scanf("%d%d%d", &n, &p, &q);
    vector<int> dep(n), par(n, -1);
    vector<vector<int> > e(n);
    for(int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        par[v] = u;
    }
    queue<int> que;
    for(int i = 0; i < n; ++i)
        if(par[i] == -1) {
            dep[i] = 1;
            que.push(i);
        }
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        for(int v: e[u]) {
            dep[v] = dep[u] + 1;
            que.push(v);
        }
    }
    int x = p, y = q;
    while(x != y) {
        if(dep[x] < dep[y])
            swap(x, y);
        x = par[x];
    }
    printf("%d %d\n", dep[p] - dep[x] + dep[q] - dep[x], dep[q] - dep[p]);
    return 0;
}
