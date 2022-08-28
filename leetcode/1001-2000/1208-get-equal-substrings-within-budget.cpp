class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int ans = 0, n = s.size();
        for(int i = 0, j = 0, c = 0; i < n; ++i) {
            for( ; j < n && c <= maxCost; c += abs(s[j] - t[j]), ++j);
            ans = max(ans, j + (c <= maxCost) - i - 1);
            c -= abs(s[i] - t[i]);
        }
        return ans;
    }
};
