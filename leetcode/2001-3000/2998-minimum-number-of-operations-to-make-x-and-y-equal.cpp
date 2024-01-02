class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        static const int maxn = (int)1e4 + 1;
        static int st = 0, tim[maxn] = {}, dp[maxn];
        if(!(++st)) {
            memset(tim, 0, sizeof tim);
            ++st;
        }
        tim[y] = st;
        dp[y] = 0;
        function<int(int)> calc = [&](int x) {
            if(tim[x] != st) {
                tim[x] = st;
                dp[x] = abs(x - y);
                for(int d = 5; d <= 11; d += 6) {
                    int q = x / d, r = x % d;
                    // printf("%d -> %d: %d\n", q, x, r + 1);
                    dp[x] = min(dp[x], calc(q) + r + 1);
                    if(r > 0) {
                        // printf("%d -> %d: %d\n", q + 1, x, d - r + 1);
                        dp[x] = min(dp[x], calc(q + 1) + (d - r) + 1);
                    }
                }
                // printf("%d: %d\n", x, dp[x]);
            }
            return dp[x];
        };
        return calc(x);
    }
};
