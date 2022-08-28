class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> ret(1 << n);
        for(int i = 0; i < (1 << n); ++i)
            ret[i] = i ^ (i >> 1);
        return ret;
    }
};
