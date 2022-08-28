class Solution {
public:
    int domino(int r, int c, vector<vector<int>>& broken) {
        int n = r * c;
        vector<vector<int> > e(n);
        vector<int> match(n, -1);
        vector<bool> ban(n), vis(n);
        for(auto &it: broken)
            ban[it[0] * c + it[1]] = 1;
        for(int i = 0, j, x = 0; x < r; ++x)
            for(int y = 0; y < c; ++y, ++i) {
                if(ban[i])
                    continue;
                if(x > 0 && !ban[j = i - c]) {
                    e[i].push_back(j);
                    e[j].push_back(i);
                }
                if(y > 0 && !ban[j = i - 1]) {
                    e[i].push_back(j);
                    e[j].push_back(i);
                }
            }
        int ans = 0;
        function<bool(int)> path = [&](int u) -> bool {
            for(int v: e[u]) {
                if(vis[v])
                    continue;
                vis[v] = 1;
                if(match[v] == -1 || path(match[v])) {
                    match[v] = u;
                    return 1;
                }
            }
            return 0;
        };
        for(int i = 0, x = 0; x < r; ++x)
            for(int y = 0; y < c; ++y, ++i) {
                if((x & 1) != (y & 1) || ban[i])
                    continue;
                vis.assign(n, false);
                ans += path(i);
            }
        return ans;
    }
};
