class Solution {
public:
    int maximumInvitations(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), ans = 0;
        vector<int> match(m, -1);
        vector<bool> vis(m);
        function<bool(int)> path = [&](int u) -> bool {
            for(int v = 0; v < m; ++v) {
                if(!grid[u][v] || vis[v])
                    continue;
                vis[v] = 1;
                if(match[v] == -1 || path(match[v])) {
                    match[v] = u;
                    return 1;
                }
            }
            return 0;
        };
        for(int i = 0; i < n; ++i) {
            vis.assign(m, 0);
            ans += path(i);
        }
        return ans;
    }
};
