class Solution {
public:
    bool splitArray(vector<int>& nums) {
        // [0, i) -> [i+1, j) -> [j+1, k) -> [k+1, n)
        int n = nums.size();
        vector<int> psum = {0};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        vector<vector<int> > dp(n + 1, vector<int>(n + 1));
        unordered_map<int, int> Hash;
        for(int L = 0; L < n; ++L) {
            Hash.clear();
            for(int i = L - 2; i >= 0; --i)
                Hash[psum[L - 1] - psum[i]] |= dp[i][L - 1];
            for(int R = L + 1; R <= n; ++R) {
                dp[L][R] = !L;
                auto it = Hash.find(psum[R] - psum[L]);
                if(it != Hash.end())
                    dp[L][R] |= (it -> second & 7) << 1;
                // printf("[%d, %d): %d\n", L, R, dp[L][R]);
            }
        }
        for(int i = 0; i < n; ++i)
            if(dp[i][n] & 8)
                return 1;
        return 0;
    }
};
