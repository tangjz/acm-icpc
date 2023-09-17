class Solution {
public:
    int numberOfSpecialSubstrings(string s) {
        int ans = 0, n = s.size();
        for(char &ch: s)
            ch -= 'a';
        for(int i = 0, j = 0, msk = 0; i < n; ++i) {
            for( ; j < n && !(msk & (1 << s[j])); msk |= 1 << s[j++]);
            ans += j - i;
            msk ^= 1 << s[i];
        }
        return ans;
    }
};
