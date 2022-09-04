class Solution {
public:
    bool halvesAreAlike(string s) {
        static bool sp[257] = {};
        if(!sp['a'])
            for(char ch: "aeiou")
                sp[ch] = 1;
        int n = s.size() / 2, ans = 0;
        for(int i = 0; i < n; ++i) {
            ans += sp[tolower(s[i])];
            ans -= sp[tolower(s[n + i])];
        }
        return !ans;
    }
};
