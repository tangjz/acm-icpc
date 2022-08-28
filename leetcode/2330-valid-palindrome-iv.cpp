class Solution {
public:
    bool makePalindrome(string s) {
        int n = s.size(), m = 0;
        for(int i = 0, j = n - 1; i < j && m <= 2; ++i, --j)
            m += s[i] != s[j];
        return m <= 2;
    }
};
