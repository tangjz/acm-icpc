class Solution {
public:
    int maximumCostSubstring(string s, string chars, vector<int>& vals) {
        const int maxc = 26;
        int m = vals.size();
        vector<int> cost(maxc, INT_MIN);
        for(int i = 0; i < m; ++i) {
            int o = chars[i] - 'a';
            cost[o] = vals[i];
        }
        for(int i = 0; i < maxc; ++i)
            if(cost[i] == INT_MIN)
                cost[i] = i + 1;
        int ans = 0, pre = 0, cur = 0;
        for(char ch: s) {
            pre = min(pre, cur);
            int o = ch - 'a';
            cur += cost[o];
            ans = max(ans, cur - pre);
        }
        return ans;
    }
};
