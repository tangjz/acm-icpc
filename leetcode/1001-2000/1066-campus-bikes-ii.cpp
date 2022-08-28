class Solution {
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        const int INF = 0x3f3f3f3f;
        int n = workers.size(), m = bikes.size();
        vector<int> f(1 << n, INF);
        f[0] = 0;
        for(int i = 0; i < m; ++i) {
            vector<int> g(1 << n, INF);
            for(int j = 0; j < n; ++j)  {
                int cost = abs(bikes[i][0] - workers[j][0]) + abs(bikes[i][1] - workers[j][1]);
                for(int k = 0; k < (1 << n); ++k)
                    if((k >> j) & 1)
                        g[k] = min(g[k], f[k ^ (1 << j)] + cost);
            }
            for(int k = 0; k < (1 << n); ++k)
                f[k] = min(f[k], g[k]);
        }
        return f.back();
    }
};
