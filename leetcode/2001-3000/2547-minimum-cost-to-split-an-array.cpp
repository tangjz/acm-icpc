class Solution {
public:
    int minCost(vector<int>& A, int k) {
        int n = A.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            int adt = 0;
            static unordered_map<int, int> ctr;
            ctr.clear();
            for(int j = i; j < n; ++j) {
                adt += (ctr[A[j]]++) == 1;
                int cost = k + j - i + 1 - ctr.size() + adt;
                // printf("cost [%d, %d]: %d\n", i, j, cost);
                dp[j + 1] = min(dp[j + 1], dp[i] + cost);
            }
        }
        return dp[n];
    }
};
