class Solution {
public:
    vector<int> circularPermutation(int n, int start) {
        int pos = -1, tot = 1 << n;
        vector<int> ret;
        ret.reserve(tot);
        for(int i = 0; i < tot; ++i) {
            ret.push_back((i >> 1) ^ i);
            if(ret.back() == start)
                pos = i;
        }
        rotate(ret.begin(), ret.begin() + pos, ret.end());
        return ret;
    }
};
