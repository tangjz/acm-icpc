class Solution {
public:
    int numWays(int steps, int arrLen) {
        const int mod = (int)1e9 + 7;
        arrLen = min(arrLen, (steps >> 1) + 1);
        vector<int> f(arrLen);
        f[0] = 1;
        for(int i = 0; i < steps; ++i) {
            vector<int> g(arrLen);
            for(int j = 0; j < arrLen; ++j) {
                if(!f[j])
                    continue;
                for(int k = max(j - 1, 0), kLim = min(j + 1, arrLen - 1); k <= kLim; ++k)
                    (g[k] += f[j]) >= mod && (g[k] -= mod);
            }
            f = move(g);
        }
        return f[0];
    }
};
