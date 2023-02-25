class Solution {
public:
    int longestContinuousSubstring(string s) {
        int ans = 0, n = s.size();
        for(int i = 0, j; i < n; ) {
            for(j = i++; i < n && s[i] == s[i - 1] + 1; ++i);
            ans = max(ans, i - j);
        }
        return ans;
    }
};
