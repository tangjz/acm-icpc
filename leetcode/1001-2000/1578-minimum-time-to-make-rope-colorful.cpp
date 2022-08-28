class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        int n = (int)s.size(), ans = 0;
        for(int i = 0, j; i < n; ) {
            int mx = 0;
            for(j = i; i < n && s[i] == s[j]; ++i) {
                ans += cost[i];
                mx = max(mx, cost[i]);
            }
            ans -= mx;
        }
        return ans;
    }
};
