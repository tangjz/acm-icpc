class Solution {
public:
    string baseNeg2(int n) {
        string ret = "";
        while(n != 0) {
            ret.push_back('0' + (n & 1));
            n = -(n >> 1);
        }
        reverse(ret.begin(), ret.end());
        if(ret == "")
            ret.push_back('0');
        return ret;
    }
};
