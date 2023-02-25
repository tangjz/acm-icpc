class Solution {
public:
    int minOperations(int n) {
        static const int maxL = 18, maxv = 1 << maxL | 1;
        static int dp[maxv] = {-1};
        if(dp[0] == -1) {
            queue<int> que;
            memset(dp, -1, sizeof dp);
            auto upd = [&](int x, int d) {
                if(x < 0 || x >= maxv || dp[x] != -1)
                    return;
                dp[x] = d;
                que.push(x);
            };
            upd(0, 0);
            while(!que.empty()) {
                int u = que.front();
                que.pop();
                for(int i = 0; i < maxL; ++i) {
                    upd(u + (1 << i), dp[u] + 1);
                    upd(u - (1 << i), dp[u] + 1);
                }
            }
        }
        return dp[n];
    }
};
