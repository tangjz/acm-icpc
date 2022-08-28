class Solution {
public:
    int findRotateSteps(string ring, string key) {
        const int INF = 0x3f3f3f3f;
        int n = ring.size(), m = key.size();
        vector<int> f(n, INF);
        f[0] = 0;
        for(char ch: key) {
            vector<int> g(n, INF);
            for(int i = 0; i < n; ++i) {
                if(ring[i] != ch)
                    continue;
                for(int j = 0; j < n; ++j) {
                    int dis = abs(i - j);
                    dis = min(dis, n - dis);
                    g[i] = min(g[i], f[j] + dis);
                }
                ++g[i];
            }
            f = move(g);
        }
        return *min_element(f.begin(), f.end());
    }
};
