class Solution {
public:
    string maximumOddBinaryNumber(string s) {
        sort(s.begin(), s.end());
        reverse(s.begin(), s.end() - 1);
        return s;
    }
};
