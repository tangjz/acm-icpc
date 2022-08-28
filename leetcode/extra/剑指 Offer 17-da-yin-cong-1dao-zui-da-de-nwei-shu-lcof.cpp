class Solution {
public:
    vector<int> printNumbers(int n) {
        int pw = 1;
        for(int i = 0; i < n; ++i)
            pw *= 10;
        vector<int> ret(pw - 1);
        iota(ret.begin(), ret.end(), 1);
        return ret;
    }
};
