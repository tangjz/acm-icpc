class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for(int i = 0; i < n; i += k + k) {
            int j = min(i + k, n);
            reverse(s.begin() + i, s.begin() + j);
        }
        return s;
    }
};
