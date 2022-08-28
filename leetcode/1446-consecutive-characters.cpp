class Solution {
public:
    int maxPower(string s) {
        int mx = 0, las = 0, pos = 0;
        for(char ch : s) {
            if(ch != s[las]) {
                las = pos;
            }
            mx = max(mx, pos - las + 1);
            ++pos;
        }
        return mx;
    }
};
