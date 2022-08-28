class Solution {
public:
    string reverseOnlyLetters(string s) {
        int L = 0, R = s.size() - 1;
        while(L < R) {
            for( ; L < R && !isalpha(s[L]); ++L);
            for( ; L < R && !isalpha(s[R]); --R);
            if(L < R)
                swap(s[L++], s[R--]);
        }
        return move(s);
    }
};
