class Solution {
public:
    string kthLuckyNumber(int k) {
        int len = 1;
        for( ; k > (1 << len); k -= 1 << (len++));
        --k;
        string ret = "";
        ret.reserve(len);
        for( ; len > 0; --len, ret.push_back("47"[k & 1]), k >>= 1);
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
