class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        const int INF = 0x3f3f3f3f;
        vector<int> f(n, INF);
        f[src] = 0;
        ++K;
        while(K--) {
            vector<int> g(f.begin(), f.end());
            for(auto &it : flights)
                g[it[1]] = min(g[it[1]], f[it[0]] + it[2]);
            f = move(g);
        }
        return f[dst] < INF ? f[dst] : -1;
    }
};
