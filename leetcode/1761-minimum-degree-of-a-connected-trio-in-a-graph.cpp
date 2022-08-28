class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<int> deg(n);
        vector<vector<int> > e(n, vector<int>(n));
        for(auto &it: edges) {
            int u = it[0] - 1, v = it[1] - 1;
            ++deg[u];
            ++deg[v];
            e[u][v] = e[v][u] = 1;
        }
        int ans = INT_MAX;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                if(!e[i][j])
                    continue;
                for(int k = j + 1; k < n; ++k)
                    if(e[i][k] && e[j][k])
                        ans = min(ans, deg[i] + deg[j] + deg[k]);
            }
        return ans < INT_MAX ? ans - 6 : -1;
    }
};
