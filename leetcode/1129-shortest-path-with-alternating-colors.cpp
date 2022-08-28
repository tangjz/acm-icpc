class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<vector<vector<int> > > e(2, vector<vector<int> >(n));
        for(auto &it: redEdges)
            e[0][it[0]].push_back(it[1]);
        for(auto &it: blueEdges)
            e[1][it[0]].push_back(it[1]);
        vector<vector<int> > dis(2, vector<int>(n, -1));
        queue<pair<int, int> > que;
        auto upd = [&](int t, int u, int d) {
            if(dis[t][u] != -1)
                return;
            dis[t][u] = d;
            que.push({t, u});
        };
        upd(0, 0, 0);
        upd(1, 0, 0);
        while(!que.empty()) {
            int t, u;
            tie(t, u) = que.front();
            que.pop();
            for(int v: e[t][u])
                upd(!t, v, dis[t][u] + 1);
        }
        vector<int> ret(n, -1);
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < n; ++j)
                if(ret[j] == -1 || (dis[i][j] != -1 && dis[i][j] < ret[j]))
                    ret[j] = dis[i][j];
        return ret;
    }
};
