class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = (int)s.size();
        vector<int> f(n + 1);
        for(int i = 1, j = 0; i < n; ++i) {
            for( ; j && s[i] != s[j]; j = f[j]);
            f[i + 1] = s[i] == s[j] ? (++j) : 0;
        }
        return f[n] > 0 && n % (n - f[n]) == 0;
    }
};
