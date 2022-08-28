class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        vector<int> lft(time + 1, INT_MAX);
        for(auto &it: clips) {
            if(it[0] == it[1] || it[0] > time)
                continue;
            it[1] = min(it[1], time);
            lft[it[1]] = min(lft[it[1]], it[0]);
        }
        vector<int> dp(time + 1, INT_MAX), stk;
        dp[0] = 0;
        stk.push_back(0);
        for(int i = 1; i <= time; ++i) {
            if(lft[i] <= stk.back()) {
                dp[i] = dp[*lower_bound(stk.begin(), stk.end(), lft[i])] + 1;
            }
            while(!stk.empty() && dp[stk.back()] >= dp[i])
                stk.pop_back();
            if(dp[i] < INT_MAX)
                stk.push_back(i);
        }
        int &ans = dp.back();
        return ans < INT_MAX ? ans : -1;
    }
};
