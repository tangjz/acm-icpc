class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& w) {
        int n = w.size();
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<int> dis(n, -1);
        queue<int> que;
        auto upd = [&](int x, int t) {
            if(dis[x] != -1)
                return;
            dis[x] = t;
            que.push(x);
        } ;
        upd(0, 0);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: e[u])
                upd(v, dis[u] + 1);
        }
        int ans = 0;
        for(int i = 1; i < n; ++i) {
            int len = dis[i] << 1;
            int las = max((len - 1) / w[i] * w[i], 0);
            ans = max(ans, las + len);
        }
        return ans + 1;
    }
};
