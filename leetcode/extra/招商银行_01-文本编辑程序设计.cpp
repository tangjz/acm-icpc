class Solution {
public:
    string deleteText(string s, int p) {
        if(s[p] == ' ')
            return s;
        int n = s.size(), L = p, R = p;
        for( ; L > 0 && isalpha(s[L - 1]); --L);
        for( ; R < n && isalpha(s[R]); ++R);
        if(R < n && s[R] == ' ')
            ++R;
        if(R == n && L > 0 && s[L - 1] == ' ')
            --L;
        return s.substr(0, L) + s.substr(R);
    }
};
