class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int n = s.size(), las0 = -1, las1 = -1, ans = 0;
        auto upd = [&](int x) {
            if(las1 >= 0) {
                ans = max(ans, x - las0);
            }
            las0 = las1;
            las1 = x;
        };
        for(int i = 0; i + 1 < n; ++i)
            if(s[i] == s[i + 1])
                upd(i);
        upd(n - 1);
        if(las0 == -1)
            ans = n;
        return ans;
    }
};
