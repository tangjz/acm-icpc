class Solution {
public:
    int appendCharacters(string s, string t) {
        int m = t.size(), p = 0;
        for(char ch: s)
            p += p < m && ch == t[p];
        return m - p;
    }
};
