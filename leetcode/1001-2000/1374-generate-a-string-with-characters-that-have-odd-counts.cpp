class Solution {
public:
    string generateTheString(int n) {
        string ret = string(n - !(n & 1), 'a');
        if(ret.size() < n)
            ret += 'b';
        return ret;
    }
};
