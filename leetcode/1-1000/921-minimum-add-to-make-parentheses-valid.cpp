class Solution {
public:
    int minAddToMakeValid(string s) {
        int cR = 0, cL = 0;
        for(char ch: s)
            if(ch == '(') {
                ++cL;
            } else {
                cL ? --cL : ++cR;
            }
        return cL + cR;
    }
};
