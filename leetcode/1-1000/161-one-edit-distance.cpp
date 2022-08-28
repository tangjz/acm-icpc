class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if(s.size() == t.size()) {
            int n = s.size(), c = 0;
            for(int i = 0; c <= 1 && i < n; ++i)
                c += s[i] != t[i];
            return c == 1;
        }
        if(s.size() < t.size())
            s.swap(t);
        if(s.size() - t.size() > 1)
            return 0;
        int m = t.size(), p = 0;
        if(p == m)
            return 1;
        for(char ch: s)
            if(ch == t[p] && (++p) == m)
                return 1;
        return 0;
    }
};
