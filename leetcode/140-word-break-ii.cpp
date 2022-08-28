class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int slen = (int)s.length(), tlen = 0;
        vector<unordered_set<string> > Hash;
        for(auto &it : wordDict) {
            int len = (int)it.length();
            for( ; tlen < len; ++tlen)
                Hash.push_back(unordered_set<string>());
            Hash[len - 1].insert(it);
        }
        vector<vector<int> > dp(slen + 1, vector<int>());
        dp[slen].push_back(0);
        for(int i = slen - 1; i >= 0; --i) {
            string cur = "";
            for(int j = 0; j < tlen && i + j < slen; ++j) {
                cur += s[i + j];
                if(dp[i + j + 1].size() && Hash[j].count(cur))
                    dp[i].push_back(j);
            }
        }
        vector<string> ret;
        function<void(int, string)> dfs = [&](int pos, string cur) {
            if(pos == slen) {
                ret.push_back(cur);
            } else {
                if(cur != "")
                    cur += ' ';
                auto it = dp[pos].begin();
                for(int j = 0; j < tlen && pos + j < slen && it != dp[pos].end(); ++j) {
                    cur += s[pos + j];
                    if(*it == j) {
                        dfs(pos + j + 1, cur);
                        ++it;
                    }
                }
            }
        };
        dfs(0, "");
        return ret;
    }
};
