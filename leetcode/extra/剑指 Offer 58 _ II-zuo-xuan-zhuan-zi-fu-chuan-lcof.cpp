class Solution {
public:
    string reverseLeftWords(string s, int n) {
        rotate(s.begin(), s.begin() + n, s.end());
        return s;
    }
};
