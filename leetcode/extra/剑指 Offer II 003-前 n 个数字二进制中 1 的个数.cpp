class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ret = {0};
        ret.reserve(num + 1);
        for(int i = 1; i <= num; ++i)
            ret.push_back(ret[i >> 1] + (i & 1));
        return ret;
    }
};
