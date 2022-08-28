class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        vector<vector<int> > e(n, vector<int>());
        int pos = 0;
        for(int p : manager) {
            if(p >= 0)
                e[p].push_back(pos);
            ++pos;
        }
        int ans = 0;
        function<void(int, int)> dfs = [&](int u, int tim) {
            ans = max(ans, tim);
            tim += informTime[u];
            for(int v : e[u])
                dfs(v, tim);
        };
        dfs(headID, 0);
        return ans;
    }
};
