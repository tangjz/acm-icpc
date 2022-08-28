class Solution {
public:
    int titleToNumber(string s) {
        static const int maxd = 26;
        int ret = 0, cnt = 0;
        for(char ch : s) {
            ret = ret * maxd + (ch - 'A');
            ++cnt;
        }
        for(int i = 1, pw = 1; i < cnt; ++i) {
            pw *= maxd;
            ret += pw;
        }
        return ++ret;
    }
};
