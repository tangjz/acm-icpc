class Solution {
public:
    int minLength(string s) {
        int n = 0;
        for(char ch: s) {
            if(ch == 'B' && n > 0 && s[n - 1] == 'A') {
                --n;
                continue;
            }
            if(ch == 'D' && n > 0 && s[n - 1] == 'C') {
                --n;
                continue;
            }
            s[n++] = ch;
        }
        return n;
    }
};
