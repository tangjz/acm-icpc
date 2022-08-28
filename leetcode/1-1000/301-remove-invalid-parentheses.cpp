class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int n = (int)s.length();
        vector<vector<int> > dp(n + 1, vector<int>());
        dp[n].push_back(0);
        for(int i = n - 1; i >= 0; --i) {
            int sgn = s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0);
            if(!sgn) {
                dp[i] = dp[i + 1];
                continue;
            }
            int psz = (int)dp[i + 1].size(), csz = psz + (sgn < 0);
            for(int j = 0, k = sgn; j < csz; ++j, ++k) {
                int cost = j < psz ? dp[i + 1][j] + 1 : n + 1;
                if(k >= 0 && k < psz)
                    cost = min(cost, dp[i + 1][k]);
                dp[i].push_back(cost);
            }
        }
        unordered_set<string> Hash;
        function<void(int, int, string &)> dfs = [&](int i, int j, string &cur) {
            if(i == n) {
                Hash.insert(cur);
            } else {
                int sgn = s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0);
                int nsz = (int)dp[i + 1].size(), k = j + sgn;
                if(k >= 0 && k < nsz && dp[i + 1][k] == dp[i][j]) {
                    cur += s[i];
                    dfs(i + 1, k, cur);
                    cur.pop_back();
                }
                if(sgn != 0 && j < nsz && dp[i + 1][j] + 1 == dp[i][j] && (!cur.length() || cur.back() != s[i]))
                    dfs(i + 1, j, cur);
            }
        };
        string cur = "";
        dfs(0, 0, cur);
        return vector<string>(Hash.begin(), Hash.end());
    }
};
