class Solution {
public:
    int numDecodings(string s) {
        const int maxd = 26;
        int dp0 = 0, dp1 = 0, pre = maxd + 1, cur;
        dp0 = 1;
        for(char ch : s) {
            cur = ch - '0';
            pre += cur;
            tie(dp0, dp1) = make_pair((cur > 0 ? dp0 : 0) + (pre > 0 && pre <= maxd ? dp1 : 0), dp0);
            pre = cur > 0 ? cur * 10 : maxd + 1;
        }
        return dp0;
    }
};
