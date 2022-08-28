class Solution {
public:
    bool isMatch(string s, string p) {
        string pat;
        vector<char> sp;
        for(char ch : p)
            if(ch == '*') {
                sp.back() = 1;
            } else {
                pat += ch;
                sp.push_back(0);
            }
        int n = (int)pat.length();
        vector<char> dp(n + 1, 0);
        dp[0] = 1;
        for(int i = 0; i < n && sp[i]; ++i)
            dp[i + 1] = 1;
        for(char ch : s) {
            bool las = dp[0], cur;
            dp[0] = dp[0] && n > 0 && sp[0] && (pat[0] == '.' || pat[0] == ch);
            for(int i = 0; i < n; ++i) {
                cur = dp[i + 1];
                if(!(i + 1 < n && sp[i + 1] && (pat[i + 1] == '.' || pat[i + 1] == ch)))
                    dp[i + 1] = 0;
                if(sp[i])
                    dp[i + 1] |= dp[i];
                if(pat[i] == '.' || pat[i] == ch)
                    dp[i + 1] |= las;
                las = cur;
            }
        }
        return dp[n];
    }
};
