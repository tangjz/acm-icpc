class Solution {
public:
    int bulbSwitch(int n) {
        int m = floor(sqrtl(n));
        for( ; (m + 1) * (m + 1) <= n; ++m);
        return m;
    }
};
