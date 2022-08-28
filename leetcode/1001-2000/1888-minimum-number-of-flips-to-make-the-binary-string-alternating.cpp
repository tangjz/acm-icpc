class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        vector<int> pre(n), suf(n);
        for(int i = 0; i < n; ++i) {
            pre[i] = (s[i] == '1') + (i > 1 ? pre[i - 2] : 0);
        }
        for(int i = n - 1; i >= 0; --i) {
            suf[i] = (s[i] == '1') + (i + 2 < n ? suf[i + 2] : 0);
        }
        int ans = n;
        for(int i = 0; i < n; ++i) {
            int lenR = n - i, lenL = i;
            int lenRO = lenR >> 1, lenRE = lenR - lenRO;
            int lenLO = lenL >> 1, lenLE = lenL - lenLE;
            int c0 = suf[i] + (i + 1 < n ? lenRO - suf[i + 1] : 0);
            if(lenL > 0) {
                int cL = pre[i - 1] + (i - 2 >= 0 ? lenLO - pre[i - 2] : 0);
                c0 += n & 1 ? cL : lenL - cL;
            }
            ans = min(ans, min(c0, n - c0));
        }
        return ans;
    }
};
