class Solution {
public:
    bool canBeValid(string s, string locked) {
        int n = s.size();
        puts("");
        if(n & 1)
            return false;
        int cL = 0, cR = 0;
        for(int i = 0; i < n; ++i) {
            if(locked[i] == '0') {
                s[i] = '.';
                continue;
            }
            if(s[i] == '(') {
                ++cR;
            } else {
                cR > 0 ? (--cR) : (++cL);
            }
        }
        // printf("%d %d\n", cL, cR);
        for(int i = 0; i < n && cL > 0; ++i) {
            if(s[i] == '.') {
                s[i] = '(';
                --cL;
            }
        }
        for(int i = n - 1; i >= 0 && cR > 0; --i) {
            if(s[i] == '.') {
                s[i] = ')';
                --cR;
            }
        }
        // printf("%d %d\n", cL, cR);
        if(cL > 0 || cR > 0)
            return false;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '(') {
                ++cR;
            } else if(s[i] == ')') {
                cR > 0 ? (--cR) : (++cL);
            }
        }
        // printf("%d %d\n", cL, cR);
        return !cL && !cR;
    }
};
