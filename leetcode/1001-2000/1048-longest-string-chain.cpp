class Solution {
    bool check(string const &a, string const &b) {
        int m = b.size(), pos = 0;
        for(char ch: a) {
            pos += ch == b[pos];
            if(pos == m)
                return 1;
        }
        return 0;
    }
public:
    int longestStrChain(vector<string>& words) {
        int n = words.size(), ans = 0;
        vector<int> dp(n);
        sort(words.begin(), words.end(), [&](string const &u, string const &v) {
            return u.size() < v.size();
        });
        for(int i = 0; i < n; ++i) {
            dp[i] = 1;
            for(int j = 0; j < i; ++j)
                if(words[j].size() + 1 == words[i].size() && dp[i] < dp[j] + 1 && check(words[i], words[j])) {
                    dp[i] = dp[j] + 1;
                }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
