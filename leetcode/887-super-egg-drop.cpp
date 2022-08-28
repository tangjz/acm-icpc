class Solution {
public:
    int superEggDrop(int K, int N) {
        int M = N;
        vector<int> dp(N + 1, 0);
        for(int i = 1; i <= K; ++i) {
            int las = dp[0], cur;
            for(int j = 1; j <= M; ++j) {
                cur = dp[j];
                dp[j] = las + dp[j - 1] + 1;
                if(dp[j] >= N) {
                    M = j;
                    break;
                }
                las = cur;
            }
        }
        return M;
    }
};
