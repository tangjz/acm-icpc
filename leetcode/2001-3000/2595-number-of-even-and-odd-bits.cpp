class Solution {
public:
    vector<int> evenOddBit(int n) {
        int cnt[2] = {};
        for(int o = 0; n > 0; o = !o, n >>= 1) {
            if(n & 1)
                ++cnt[o];
        }
        return {cnt[0], cnt[1]};
    }
};
