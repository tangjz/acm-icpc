class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string> > dp(n + 1);
        dp[0].push_back("");
        for(int i = 1; i <= n; ++i)
            for(int j = 0, k = i - 1; k >= 0; ++j, --k)
                for(auto &it: dp[j])
                    for(auto &jt: dp[k])
                        dp[i].push_back("(" + it + ")" + jt);
        return dp.back();
    }
};
