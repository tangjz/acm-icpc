class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        const int INF = 0x3f3f3f3f;
        int n = cost.size(), m = cost[0].size();
        vector<int> f(1 << m, INF);
        f[0] = 0;
        for(auto &vec: cost) {
            vector<int> g(1 << m, INF);
            for(int i = 0, s = 1; i < m; ++i, s <<= 1) {
                for(int t = 0; t < (1 << m); ++t)
                    if(s & t)
                        g[t] = min(g[t], min(min(f[t ^ s], f[t]), g[t ^ s]) + vec[i]);
            }
            f = move(g);
        }
        return f.back();
    }
};
