class Solution {
public:
    int alternateDigitSum(int n) {
        string s = to_string(n);
        int ans = 0, m = s.size();
        for(int i = 0; i < m; ++i) {
            int v = s[i] - '0';
            ans += i & 1 ? -v : v;
        }
        return ans;
    }
};
