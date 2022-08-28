class Solution {
public:
    int arrangeCoins(int n) {
        int x = (int)floor(sqrtl(2LL * n + 1.0 / 4) - 1.0 / 2);
        for( ; x * (x + 1LL) <= 2LL * n; ++x);
        for( ; x * (x + 1LL) > 2LL * n; --x);
        return x;
    }
};
