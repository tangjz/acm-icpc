class Solution {
public:
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        typedef long long LL;
        vector<vector<int> > e(n);
        vector<int> par(n);
        vector<LL> dis(n), dis2(n);
        vector<bool> ban(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        function<LL(int)> dfs = [&](int u) {
            LL ret = dis[u] - price[u];
            for(int v: e[u])
                if(v != par[u] && !ban[v]) {
                    par[v] = u;
                    dis[v] = dis[u] + price[v];
                    ret = max(ret, dfs(v));
                }
            return ret;
        };
        par[0] = -1;
        dis[0] = price[0];
        dfs(0);
        int rt = max_element(dis.begin(), dis.end()) - dis.begin();
        par[rt] = -1;
        dis[rt] = price[rt];
        dfs(rt);
        int tr = max_element(dis.begin(), dis.end()) - dis.begin();
        vector<int> seq;
        seq.push_back(tr);
        ban[tr] = 1;
        while(tr != rt) {
            tr = par[tr];
            seq.push_back(tr);
            ban[tr] = 1;
        }
        int m = seq.size();
        LL ans = 0, pre = 0;
        for(int i = 0; i < m; ++i) {
            dis[seq[i]] = price[seq[i]];
            dis2[i] = dfs(seq[i]);
            // printf("dis2 %d: %lld\n", i, dis2[i]);
            ans = max(ans, pre + dis2[i]);
            pre += price[seq[i]];
        }
        pre = 0;
        for(int i = m - 1; i >= 0; --i) {
            ans = max(ans, + pre + dis2[i]);
            pre += price[seq[i]];
        }
        return ans;
    }
};
