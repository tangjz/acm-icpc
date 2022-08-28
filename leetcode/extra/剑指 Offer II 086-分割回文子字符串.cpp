class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = (int)s.length();
        vector<vector<int> > dp(n + 1);
        vector<int> cand;
        dp[n].push_back(0);
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
                if(dp[j].size())
                    dp[i].push_back(j);
        }
        vector<vector<string> > ret;
        function<void(int, vector<string> &)> dfs = [&](int pos, vector<string> &cur) {
            if(pos == n) {
                ret.push_back(cur);
            } else {
                auto it = dp[pos].begin();
                cur.push_back("");
                for(int j = pos + 1; j <= n && it != dp[pos].end(); ++j) {
                    cur.back() += s[j - 1];
                    if(*it == j) {
                        dfs(j, cur);
                        ++it;
                    }
                }
                cur.pop_back();
            }
        };
        vector<string> temp;
        dfs(0, temp);
        return ret;
    }
};
