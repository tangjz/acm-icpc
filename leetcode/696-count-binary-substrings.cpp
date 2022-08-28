class Solution {
public:
    int countBinarySubstrings(string s) {
        int ans = 0, n = s.size(), las = 0;
        for(int i = 0, j; i < n; ) {
            for(j = i; i < n && s[j] == s[i]; ++i);
            ans += min(las, i - j);
            las = i - j;
        }
        return ans;
    }
};
