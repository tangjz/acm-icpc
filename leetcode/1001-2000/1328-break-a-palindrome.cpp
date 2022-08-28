class Solution {
public:
    string breakPalindrome(string p) {
        int len = (int)p.size();
        if(len == 1)
            return "";
        int pos = 0, half = len >> 1;
        for( ; pos < half && p[pos] == 'a'; ++pos);
        if(pos == half) {
            p[len - 1] = 'b';
        } else {
            p[pos] = 'a';
        }
        return p;
    }
};
