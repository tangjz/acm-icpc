class Solution {
public:
    string makeSmallestPalindrome(string s) {
        int n = s.size();
        for(int i = 0, j = n - 1; i < j; ++i, --j) {
            char ch = min(s[i], s[j]);
            s[i] = s[j] = ch;
        }
        return s;
    }
};
