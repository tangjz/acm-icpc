class Solution {
public:
    int minimizedStringLength(string s) {
        unordered_set<char> sp(s.begin(), s.end());
        return sp.size();
    }
};
