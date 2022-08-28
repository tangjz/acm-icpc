class Solution {
public:
    int minCut(string s) {
        int n = (int)s.length();
        vector<int> dp(n + 1, INT_MAX), cand;
        dp[n] = -1;
        for(int i = n - 1; i >= 0; --i) {
            vector<int> temp;
            temp.push_back(i + 1);
            if(i + 1 < n && s[i] == s[i + 1])
                temp.push_back(i + 2);
            for(int j : cand)
                if(j < n && s[i] == s[j])
                    temp.push_back(j + 1);
            cand = move(temp);
            for(int j : cand)
                if(dp[j] != INT_MAX)
                    dp[i] = min(dp[i], dp[j] + 1);
        }
        return dp[0];
    }
};
