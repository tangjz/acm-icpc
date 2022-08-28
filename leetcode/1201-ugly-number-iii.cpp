class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        typedef long long LL;
        int L = 1, R = (int)2e9;
        LL ab = a / gcd(a, b) * (LL)b, ac = a / gcd(a, c) * (LL)c, bc = b / gcd(b, c) * (LL)c, abc = a / gcd((LL)a, bc) * bc;
        while(L < R) {
            LL M = L + ((R - L) >> 1);
            LL ctr = M / a + M / b + M / c - M / ab - M / ac - M / bc + M / abc;
            if(ctr >= n) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
