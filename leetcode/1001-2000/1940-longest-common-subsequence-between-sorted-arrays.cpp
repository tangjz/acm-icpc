class Solution {
public:
    vector<int> longestCommonSubsequence(vector<vector<int>>& arrays) {
        int n = arrays.size(), m = arrays[0].size();
        pair<int, int> ans = {0, -1};
        vector<int> cur(n), lim(n);
        vector<pair<int, int> > dp(m);
        for(int i = 1; i < n; ++i)
            lim[i] = arrays[i].size();
        for(int i = 0; i < m; ++i) {
            bool skip = 0;
            int val = arrays[0][i];
            for(int j = 1; j < n; ++j) {
                for( ; cur[j] < lim[j] && arrays[j][cur[j]] < val; ++cur[j]);
                if(cur[j] == lim[j] || arrays[j][cur[j]] != val) {
                    skip = 1;
                    break;
                }
            }
            if(skip)
                continue;
            dp[i] = {1, -1};
            for(int j = 0; j < i; ++j)
                if(dp[j].first)
                    dp[i] = max(dp[i], make_pair(dp[j].first + 1, j));
            ans = max(ans, {dp[i].first, i});
        }
        vector<int> ret;
        while(ans.first > 0) {
            ret.push_back(arrays[0][ans.second]);
            --ans.first;
            ans.second = dp[ans.second].second;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
