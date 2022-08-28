class Solution {
public:
    vector<int> diffWaysToCompute(string s) {
        vector<int> nums;
        string ops = "";
        for(int i = 0, n = s.size(); i < n; ) {
            if(s[i] < '0' || s[i] > '9') {
                ops.push_back(s[i++]);
                continue;
            }
            int j = i;
            for( ; i < n && s[i] >= '0' && s[i] <= '9'; ++i);
            nums.push_back(stoi(s.substr(j, i - j)));
        }
        int n = nums.size();
        vector<vector<vector<int> > > dp(n, vector<vector<int> >(n));
        for(int i = 0; i < n; ++i)
            dp[i][i].push_back(nums[i]);
        for(int len = 2; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R)
                for(int M = L; M < R; ++M)
                    for(int lft: dp[L][M])
                        for(int rht: dp[M + 1][R])
                            dp[L][R].push_back(ops[M] == '+' ? lft + rht : (ops[M] == '-' ? lft - rht : lft * rht));
        return dp[0][n - 1];
    }
};
