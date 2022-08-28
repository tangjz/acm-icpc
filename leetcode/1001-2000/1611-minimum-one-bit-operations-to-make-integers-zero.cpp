class Solution {
public:
    int minimumOneBitOperations(int n) {
        int mx = 0;
        for( ; (1 << mx) <= n; ++mx);
        int m = 0;
        bool las = 0;
        for(int i = mx - 1; i >= 0; --i) {
            bool cur = las ^ ((n >> i) & 1);
            m |= cur << i;
            las = cur;
        }
        return m;
    }
};
