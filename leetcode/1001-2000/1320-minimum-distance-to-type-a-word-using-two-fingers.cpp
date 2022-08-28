class Solution {
public:
    int minimumDistance(string word) {
        int n = (int)word.size();
        auto dist = [](int u, int v) {
            const int maxd = 6;
            return abs(u / maxd - v / maxd) + abs(u % maxd - v % maxd);
        };
        const int maxd = 26, INF = 0x3f3f3f3f;
        vector<int> f(maxd, 0);
        int las = word[0] - 'A';
        for(int i = 1; i < n; ++i) {
            int cur = word[i] - 'A', d0 = dist(las, cur);
            vector<int> g(maxd, INF);
            for(int j = 0; j < maxd; ++j) {
                int d1 = dist(j, cur);
                g[j] = min(g[j], f[j] + d0);
                g[las] = min(g[las], f[j] + d1);
            }
            las = cur;
            f = move(g);
        }
        return *min_element(f.begin(), f.end());
    }
};
