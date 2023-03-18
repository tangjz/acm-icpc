class Solution {
public:
    int splitNum(int num) {
        string s = to_string(num);
        sort(s.begin(), s.end());
        int o = 0, val[2] = {};
        for(char ch: s) {
            val[o] = val[o] * 10 + (ch - '0');
            o = !o;
        }
        return val[0] + val[1];
    }
};
