class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x), t = s;
        reverse(t.begin(), t.end());
        return s == t;
    }
};
