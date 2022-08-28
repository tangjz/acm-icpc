class Solution {
    bool check(string &s, string &t) {
        int n = s.size();
        int best = 0;
        for( ; best < n && s[best] == t[n - 1 - best]; ++best);
        if(best + best + 1 >= n)
            return true;
        int L = (n - 1) >> 1, R = n >> 1;
        for( ; L >= 0 && R < n && s[L] == s[R]; --L, ++R);
        if(L < best)
            return true;
        L = (n - 1) >> 1, R = n >> 1;
        for( ; L >= 0 && R < n && t[L] == t[R]; --L, ++R);
        return L < best;
    }
public:
    bool checkPalindromeFormation(string a, string b) {
        return check(a, b) || check(b, a);
    }
};
