class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        const int INF = 0x3f3f3f3f;
        int len, f[2] = {0, INF};
        for(len = 0; target > 0; ++len, target /= x) {
            int dig = target % x, cost = len ? len - 1 : 1;
            int g[2] = {INF, INF};
            for(int j = 0; j < 2; ++j) {
                g[0] = min(g[0], f[j] + (dig + j) * (cost + 1));
                g[1] = min(g[1], f[j] + abs(dig + j - x) * (cost + 1));
            }
            f[0] = g[0];
            f[1] = g[1];
        }
        int cost = len ? len - 1 : 1;
        return min(f[0], f[1] + cost + 1) - 1;
    }
};
