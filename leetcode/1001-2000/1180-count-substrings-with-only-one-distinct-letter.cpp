class Solution {
public:
    int countLetters(string s) {
        int ans = 0, c = 0;
        char las = '\0';
        for(char ch: s) {
            if(las != ch) {
                las = ch;
                c = 0;
            }
            ans += ++c;
        }
        return ans;
    }
};
