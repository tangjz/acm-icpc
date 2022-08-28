class Solution {
public:
    bool validPalindrome(string s) {
        int L = 0, R = (int)s.size() - 1;
        for( ; L <= R && s[L] == s[R]; ++L, --R);
        if(L > R)
            return 1;
        for(int i = 0; i < 2; ++i) {
            int pL = L + i, pR = R - !i;
            for( ; pL <= pR && s[pL] == s[pR]; ++pL, --pR);
            if(pL > pR)
                return 1;
        }
        return 0;
    }
};
