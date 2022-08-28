class Solution {
public:
    bool sumGame(string num) {
        int n = num.length() >> 1;
        int dt = 0, cL = 0, cR = 0;
        for(int i = 0; i < n; ++i) {
            char ch = num[i];
            if(ch == '?') {
                ++cL;
            } else {
                int o = ch - '0';
                dt -= o;
            }
            ch = num[n + i];
            if(ch == '?') {
                ++cR;
            } else {
                int o = ch - '0';
                dt += o;
            }
        }
        if((cL + cR) & 1)
            return true;
        int com = min(cL, cR);
        cL -= com;
        cR -= com;
        int want = (cR - cL) / 2 * 9;
        return dt + want != 0;
    }
};
