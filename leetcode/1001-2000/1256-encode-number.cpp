class Solution {
public:
    string encode(int num) {
        for(int i = 0; ; ++i) {
            if(num >= (1 << i)) {
                num -= 1 << i;
                continue;
            }
            string ret = "";
            for(int j = 0; j < i; ++j, num >>= 1)
                ret.push_back('0' + (num & 1));
            reverse(ret.begin(), ret.end());
            return ret;
        }
        return "";
    }
};
