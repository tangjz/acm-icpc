class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int> > e(n, vector<int>());
        for(auto &it : edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        int ans = 0;
        function<bool(int, int)> dfs = [&](int u, int p) {
            bool need = hasApple[u];
            for(int &v : e[u])
                if(v != p)
                    need |= dfs(v, u);
            ans += u > 0 && need;
            return need;
        };
        dfs(0, -1);
        return ans << 1;
    }
};