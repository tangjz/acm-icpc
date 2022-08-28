class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 1; i <= n; ++i) {
            int upp = INT_MIN, sum = 0;
            for(int j = i - 1; j >= 0; --j) {
                upp = max(upp, books[j][1]);
                sum += books[j][0];
                if(sum > shelfWidth)
                    break;
                dp[i] = min(dp[i], dp[j] + upp);
            }
        }
        return dp.back();
    }
};
