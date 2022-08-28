class Solution {
public:
    string longestPrefix(string s) {
        int n = (int)s.size();
        vector<int> fail(n + 1, 0);
        for(int i = 1, j = 0; i < n; ++i) {
            for( ; j && s[i] != s[j]; j = fail[j]);
            fail[i + 1] = s[i] == s[j] ? (++j) : 0;
        }
        return s.substr(0, fail[n]);
    }
};
