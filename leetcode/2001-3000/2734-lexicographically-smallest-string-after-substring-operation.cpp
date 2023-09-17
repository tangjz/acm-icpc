class Solution {
public:
    string smallestString(string s) {
        int n = s.size(), p = 0;
        for( ; p < n && s[p] == 'a'; ++p);
        if(p == n) {
            s[n - 1] = 'z';
            return s;
        }
        for( ; p < n && s[p] != 'a'; ++p)
            --s[p];
        return s;
    }
};
