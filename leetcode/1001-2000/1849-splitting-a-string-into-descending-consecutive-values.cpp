class Solution {
public:
    bool splitString(string s) {
        typedef long long LL;
        const LL maxv = (LL)1e10;
        int n = s.size();
        vector<unordered_set<LL> > dp(n);
        LL pre = 0;
        for(int i = 0; i < n; ++i) {
            auto &cur = dp[i];
            pre = min(pre * 10 + (s[i] - '0'), maxv);
            if(i + 1 < n && pre < maxv)
                cur.insert(pre);
            LL val = 0, pw = 1;
            for(int j = i - 1; j >= 0; --j, pw = min(pw * 10, maxv)) {
                val = min(val + pw * (s[j + 1] - '0'), maxv);
                if(val >= maxv)
                    break;
                if(dp[j].count(val + 1))
                    cur.insert(val);
            }
        }
        return !dp.back().empty();
    }
};
