class Solution {
public:
    string longestWord(vector<string>& words) {
        if(words.empty())
            return "";
        sort(words.begin(), words.end(), [&](auto const &u, auto const &v) {
            int dt = (int)u.size() - (int)v.size();
            return dt < 0 || (!dt && u > v);
        });
        vector<unordered_set<string> > sp(words.back().size() + 1);
        for(auto &buf: words)
            sp[buf.size()].insert(buf);
        while(!words.empty()) {
            string buf = move(words.back());
            words.pop_back();
            int n = buf.size();
            vector<int> dp(n + 1);
            dp[0] = 1;
            for(int i = 0; i < n; ++i) {
                if(!dp[i])
                    continue;
                for(int j = i + 1; j <= n - !i; ++j) {
                    if(dp[j] || sp[j - i].empty())
                        continue;
                    dp[j] = sp[j - i].count(buf.substr(i, j - i));
                }
            }
            if(dp[n])
                return buf;
        }
        return "";
    }
};
