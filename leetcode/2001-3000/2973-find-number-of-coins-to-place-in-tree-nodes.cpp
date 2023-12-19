class Solution {
public:
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        typedef long long LL;
        int n = cost.size();
        vector<int> par(n, -1), que(n);
        vector<vector<int> > e(n), low(n), upp(n);
        vector<LL> res(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        que[0] = 0;
        for(int i = 0, tot = 1; i < tot; ++i) {
            int u = que[i];
            for(int v: e[u]) {
                if(v == par[u])
                    continue;
                par[v] = u;
                que[tot++] = v;
            }
        }
        auto ins = [&](vector<int> &upp, int v) {
            for(int &x: upp)
                if(x < v)
                    swap(x, v);
            if(upp.size() < 3)
                upp.push_back(v);
        };
        for(int i = n - 1; i >= 0; --i) {
            int u = que[i], p = par[u];
            ins(upp[u], cost[u]);
            ins(low[u], -cost[u]);
            if(low[u].size() < 3) {
                res[u] = 1;
            } else {
                res[u] = max(max((LL)low[u][0] * low[u][1] * upp[u][0], (LL)upp[u][0] * upp[u][1] * upp[u][2]), 0LL);
            }
            if(p < 0)
                continue;
            for(int x: upp[u])
                ins(upp[p], x);
            for(int x: low[u])
                ins(low[p], x);
        }
        return res;
    }
};
