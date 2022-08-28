class Solution {
public:
    int minimumLength(string s) {
        int L = 0, R = s.length() - 1;
        while(R - L + 1 > 1) {
            if(s[L] != s[R])
                break;
            int p = L + 1, q = R - 1;
            for( ; p <= R && s[p] == s[L]; ++p);
            for( ; q >= L && s[q] == s[R]; --q);
            L = p;
            R = q;
        }
        return max(R - L + 1, 0);
    }
};
