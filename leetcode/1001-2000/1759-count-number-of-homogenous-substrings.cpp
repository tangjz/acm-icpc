class Solution {
public:
    int countHomogenous(string s) {
        const int mod = (int)1e9 + 7;
        int n = (int)s.size(), ans = 0;
        for(int i = 0, c = 0; i < n; ++i) {
            if(!i || s[i - 1] != s[i])
                c = 0;
            ++c;
            ans = (ans + c) % mod;
        }
        return ans;
    }
};
