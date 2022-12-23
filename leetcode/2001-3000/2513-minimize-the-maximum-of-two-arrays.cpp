class Solution {
public:
    int minimizeSet(int d1, int d2, int c1, int c2) {
        typedef long long LL;
        LL L = 0, R = (c1 + c2) * 3LL;
        LL dd = d1 / gcd(d1, d2) * (LL)d2;
        while(L < R) {
            LL M = (L + R) >> 1;
            LL xx = M / dd, x1 = M / d2 - xx, x2 = M / d1 - xx, rem = M - xx - x1 - x2;
            // printf("check %lld: %lld %lld %lld %lld\n", M, xx, x1, x2, rem);
            LL tp = min(max(c1 - x1, 0LL), rem);
            x1 += tp;
            rem -= tp;
            tp = min(max(c2 - x2, 0LL), rem);
            x2 += tp;
            rem -= tp;
            if(x1 >= c1 && x2 >= c2) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
