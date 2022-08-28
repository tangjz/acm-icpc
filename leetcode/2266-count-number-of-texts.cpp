class Solution {
public:
    int countTexts(string s) {
        const int mod = (int)1e9 + 7;
        int n = s.size();
        vector<int> f(n + 1);
        f[0] = 1;
        for(int i = 0; i < n; ++i) {
            int lim = 3 + (s[i] == '7' || s[i] == '9');
            for(int j = i; j < n && j < i + lim && s[i] == s[j]; ++j)
                (f[j + 1] += f[i]) >= mod && (f[j + 1] -= mod);
        }
        return f[n];
    }
};
