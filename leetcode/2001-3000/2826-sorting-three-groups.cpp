class Solution {
public:
    int minimumOperations(vector<int>& A) {
        int n = A.size(), dp[3] = {0, 0, 0};
        for(int x: A) {
            dp[0] = dp[0] + (x != 1);
            dp[1] = min(dp[1] + (x != 2), dp[0]);
            dp[2] = min(dp[2] + (x != 3), dp[1]);
        }
        return min(dp[0], min(dp[1], dp[2]));
    }
};
