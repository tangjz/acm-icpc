class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int> > e(n, vector<int>());
        for(auto &it : edges)
            e[it[0]].push_back(it[1]);
        int ans = 0;
        function<bool(int)> dfs = [&](int u) {
            bool need = hasApple[u];
            for(int &v : e[u])
                need |= dfs(v);
            ans += u > 0 && need;
            return need;
        };
        dfs(0);
        return ans << 1;
    }
};
