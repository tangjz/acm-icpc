class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        int mx = 0;
        for( ; (1 << mx) <= label; ++mx);
        if(!(mx & 1)) {
            label ^= (1 << (mx - 1)) - 1;
        }
        vector<int> ret;
        for(int i = mx; i > 0; --i) {
            ret.push_back(label);
            if(!(i & 1))
                ret.back() ^= (1 << (i - 1)) - 1;
            label >>= 1;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
