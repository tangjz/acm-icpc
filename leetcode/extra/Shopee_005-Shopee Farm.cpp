#include <bits/stdc++.h>
using namespace std;

const int maxn = 12, maxd = 7, maxl = 5, INF = 0x3f3f3f3f;
const int low[maxn] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
const int dis[maxn][maxn] = {
    {2, 2, 2, 3, 2, 2, 2, 3, 3, 5, 3, 3},
    {2, 2, 2, 2, 3, 2, 3, 2, 3, 3, 5, 3},
    {2, 2, 2, 2, 2, 3, 3, 3, 2, 3, 3, 5},
    {3, 2, 2, 2, 3, 3, 5, 2, 2, 2, 3, 3},
    {2, 3, 2, 3, 2, 3, 2, 5, 2, 3, 2, 3},
    {2, 2, 3, 3, 3, 2, 2, 2, 5, 3, 3, 2},
    {2, 3, 3, 5, 2, 2, 2, 3, 3, 3, 2, 2},
    {3, 2, 3, 2, 5, 2, 3, 2, 3, 2, 3, 2},
    {3, 3, 2, 2, 2, 5, 3, 3, 2, 2, 2, 3},
    {5, 3, 3, 2, 3, 3, 3, 2, 2, 2, 2, 2},
    {3, 5, 3, 3, 2, 3, 2, 3, 2, 2, 2, 2},
    {3, 3, 5, 3, 3, 2, 2, 2, 3, 2, 2, 2},
};

int main() {
    int m;
    static int cost[maxn][maxd];
    scanf("%d", &m);
    for(int i = 0; i < maxn; ++i)
        for(int j = 0; j < maxd; ++j)
            scanf("%d", cost[i] + j);
    map<vector<int>, int> Hash;
    vector<vector<int> > seq;
    vector<vector<vector<int> > > e; // e[u] = {{v, dt, inc}}
    auto getID = [&](vector<int> &vec) {
        auto ret = Hash.insert({vec, (int)Hash.size()});
        if(ret.second) {
            seq.push_back(vec);
            e.push_back({});
        }
        return ret.first -> second;
    };
    vector<int> sta(maxn, -1);
    for(int i = 0; i < maxn; ++i) {
        vector<int> vec(maxl, -1);
        vec.back() = i;
        sta[i] = getID(vec);
    }
    for(int i = 0; i < (int)seq.size(); ++i) {
        vector<int> cur = seq[i], nxt(maxl);
        for(int j = 0; j < maxn; ++j)
            for(int dt = dis[cur.back()][j]; dt <= maxd; ++dt) {
                int las = -maxd;
                for(int x = 0; x < maxl; ++x) {
                    nxt[x] = x + dt < maxl ? cur[x + dt] : -1;
                    if(cur[x] == j)
                        las = x - dt;
                }
                nxt.back() = j;
                e[i].push_back({getID(nxt), dt, cost[j][min(maxl - 1 - las, maxd) - 1]});
            }
    }
    int tot = seq.size();
    vector<vector<int> > dp(maxd, vector<int>(tot, -INF));
    for(int i = 1; i <= m; ++i) {
        vector<int> cur(tot, -INF);
        for(int j = 0; j < maxn; ++j)
            if(i >= low[j])
                cur[sta[j]] = max(cur[sta[j]], cost[j][maxd - 1]);
        for(int j = 0; j < tot; ++j)
            for(auto &it: e[j]) {
                if(i < it[1])
                    continue;
                cur[it[0]] = max(cur[it[0]], dp[(i - it[1]) % maxd][j] + it[2]);
            }
        dp[i % maxd] = move(cur);
    }
    auto &res = dp[m % maxd];
    int ans = max(0, *max_element(res.begin(), res.end()));
    printf("%d\n", ans);
    return 0;
}
