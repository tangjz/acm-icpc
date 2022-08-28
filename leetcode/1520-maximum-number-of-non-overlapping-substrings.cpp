class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        typedef pair<int, int> Seg;
        const int maxd = 26;
        int len = (int)s.size();
        vector<Seg> seg(maxd, {-1, -1}), need;
        for(int i = 0; i < len; ++i) {
            int o = (int)(s[i] - 'a');
            if(seg[o].first == -1) {
                seg[o] = {i, i};
            } else {
                seg[o].second = i;
            }
        }
        for(int i = 0; i < maxd; ++i) {
            int lft = seg[i].first, rht = seg[i].second;
            for(int j = lft + 1; j <= rht; ++j) {
                int o = (int)(s[j] - 'a');
                if(seg[o].first < lft) {
                    lft = rht = -1;
                    break;
                }
                rht = max(rht, seg[o].second);
            }
            if(lft != -1)
                need.push_back({lft, rht});
        }
        sort(need.begin(), need.end());
        int n = (int)need.size();
        typedef pair<Seg, int> Info;
        Info best = {{0, 0}, n};
        vector<Info> dp(n + 1, best);
        for(int i = n - 1; i >= 0; --i) {
            for(int j = i + 1; j < n; ++j)
                if(need[j].first > need[i].second)
                    dp[i] = max(dp[i], {dp[j].first, j});
            auto &it = dp[i].first;
            ++it.first;
            it.second -= need[i].second - need[i].first + 1;
            best = max(best, {dp[i].first, i});
        }
        vector<string> ret;
        for(int i = best.second; i < n; i = dp[i].second)
            ret.push_back(s.substr(need[i].first, need[i].second - need[i].first + 1));
        return ret;
    }
};
