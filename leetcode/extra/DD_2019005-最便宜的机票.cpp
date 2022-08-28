#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    int n, m, q;
    scanf("%d%d%d%*d", &n, &q, &m);
    vector<vector<int> > edges(m, vector<int>(4));
    vector<map<int, vector<int> > > cand(n);
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < 4; ++j)
            scanf("%d", &edges[i][j]);
        cand[edges[i][0]][edges[i][2]].push_back(i);
    }
    set<pair<int, int> > vis;
    map<pair<int, int>, LL> dis;
    priority_queue<pair<LL, pair<int, int> > > que;
    auto upd = [&](int u, int e, LL d) {
        auto it = dis.find({u, e});
        if(it == dis.end() || it -> second > d) {
            dis[{u, e}] = d;
            que.push({-d, {u, e}});
        }
    };
    upd(0, -1, 0);
    while(!que.empty()) {
        pair<int, int> u = que.top().second;
        que.pop();
        if(!vis.insert(u).second)
            continue;
        int dist = dis[u];
        if(u.second != -1) {
            auto it = cand[u.first].find(edges[u.second][2]);
            if(it == cand[u.first].end())
                continue;
            for(auto &jt: it -> second)
                upd(edges[jt][1], -1, dist + (edges[u.second][3] + edges[jt][3]) * 7 / 10);
            continue;
        }
        if(u.first == 1)
            break;
        for(auto &vec: cand[u.first])
            for(auto &it: vec.second) {
                upd(edges[it][1], -1, dist + edges[it][3]);
                upd(edges[it][1], it, dist);
            }
    }
    printf("%lld\n", dis[{1, -1}]);
    return 0;
}
