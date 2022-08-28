class Solution {
public:
    int minFlips(string target) {
        int cnt = 0;
        char las = '0';
        for(char ch : target)
            if(las != ch) {
                las = ch;
                ++cnt;
            }
        return cnt;
    }
};
