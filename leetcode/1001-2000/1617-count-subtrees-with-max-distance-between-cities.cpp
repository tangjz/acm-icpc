class Solution {
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            int u = it[0] - 1, v = it[1] - 1;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        int m = 1 << n, st = 0;
        vector<int> ret(n - 1), dis(n), tim(n);
        for(int i = 1; i < m; ++i) {
            int rem = __builtin_popcount(i), fir = __builtin_ctz(i);
            if(rem == 1)
                continue;
            int upp = 0;
            queue<int> que;
            auto upd = [&](int u, int d) {
                if(tim[u] == st || !((i >> u) & 1))
                    return;
                // printf("upd %d %d\n", u, d);
                --rem;
                tim[u] = st;
                dis[u] = d;
                upp = max(upp, d);
                que.push(u);
            };
            // printf("dist 1\n");
            ++st;
            upd(fir, 0);
            while(!que.empty()) {
                int u = que.front();
                fir = u;
                que.pop();
                for(int v: e[u])
                    upd(v, dis[u] + 1);
            }
            if(rem > 0)
                continue;
            // printf("dist 2\n");
            ++st;
            upp = 0;
            upd(fir, 0);
            while(!que.empty()) {
                int u = que.front();
                que.pop();
                for(int v: e[u])
                    upd(v, dis[u] + 1);
            }
            // printf("msk %d: rem %d upp %d\n", i, rem, upp);
            if(upp > 0)
                ++ret[upp - 1];
        }
        return ret;
    }
};
