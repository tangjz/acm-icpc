class Solution {
public:
    int getLucky(string s, int k) {
        string t = "";
        for(char ch: s)
            t += to_string(ch - 'a' + 1);
        int ret = 0;
        for(char ch: t)
            ret += ch - '0';
        for(int i = 1; i < k && ret > 9; ++i) {
            t = to_string(ret);
            ret = 0;
            for(char ch: t)
                ret += ch - '0';
        }
        return ret;
    }
};
