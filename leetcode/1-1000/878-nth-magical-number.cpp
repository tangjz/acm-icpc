class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        typedef long long LL;
        LL L = 1, R = (LL)max(a, b) * n, lcm = a / gcd(a, b) * (LL)b;
        while(L < R) {
            LL M = (L + R) >> 1;
            LL ctr = M / a + M / b - M / lcm;
            if(ctr >= n) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L % ((int)1e9 + 7);
    }
};
