class Solution {
public:
    string toHex(int num) {
        string ret = "";
        unsigned int val = num;
        for( ; val > 0; val >>= 4) {
            int rem = val & 15;
            ret.push_back(rem < 10 ? '0' + rem : 'a' + (rem - 10));
        }
        if(ret.empty())
            ret.push_back('0');
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
