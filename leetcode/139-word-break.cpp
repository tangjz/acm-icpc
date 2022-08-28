class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int slen = (int)s.length(), tlen = 0;
        vector<char> dp(slen + 1, 0);
        vector<unordered_set<string> > Hash;
        for(auto &it : wordDict) {
            int len = (int)it.length();
            for( ; tlen < len; ++tlen)
                Hash.push_back(unordered_set<string>());
            Hash[len - 1].insert(it);
        }
        dp[0] = 1;
        for(int i = 0; i < slen; ++i) {
            if(!dp[i])
                continue;
            string cur = "";
            for(int j = 0; j < tlen && i + j < slen; ++j) {
                cur += s[i + j];
                if(Hash[j].count(cur))
                    dp[i + j + 1] = 1;
            }
        }
        return dp[slen];
    }
};
