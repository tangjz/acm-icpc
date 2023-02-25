class Solution {
public:
    bool makeStringsEqual(string s, string t) {
        // 0 1 -> 1 1
        // 1 0 -> 1 1
        // 1 1 -> 1 0
        int n = s.size(), c[2] = {};
        for(char ch: s)
            c[0] += ch == '1';
        for(char ch: t)
            c[1] += ch == '1';
        if(!c[0] || !c[1])
            return !c[0] && !c[1];
        return 1;
    }
};
