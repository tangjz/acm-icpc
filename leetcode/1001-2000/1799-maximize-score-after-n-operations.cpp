class Solution {
public:
    int maxScore(vector<int>& nums) {
        int m = (int)nums.size(), d = 1 << m;
        vector<vector<int> > com(m, vector<int>(m));
        for(int i = 0; i < m; ++i)
            for(int j = i + 1; j < m; ++j)
                com[i][j] = gcd(nums[i], nums[j]);
        vector<int> bits(d, 0), dp(d, INT_MIN);
        dp[0] = 0;
        for(int i = 1; i < d; ++i) {
            bits[i] = bits[i >> 1] + (i & 1);
            if(bits[i] & 1)
                continue;
            int mul = bits[i] >> 1;
            vector<int> pos;
            for(int k = 0; k < m; ++k) {
                if(!((i >> k) & 1))
                    continue;
                for(int j : pos)
                    dp[i] = max(dp[i], dp[i ^ (1 << j) ^ (1 << k)] + mul * com[j][k]);
                pos.push_back(k);
            }
        }
        return dp[d - 1];
    }
};
