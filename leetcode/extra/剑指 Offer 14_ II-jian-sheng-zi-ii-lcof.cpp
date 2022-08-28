class Solution {
public:
    int cuttingRope(int n) {
        if(n < 2 + 2) {
            return n - 1;
        }
        static const int mod = (int)1e9 + 7;
        int prd = 1;
        while(n > 4) {
            prd = 3LL * prd % mod;
            n -= 3;
        }
        prd = 1LL * n * prd % mod;
        return prd;
    }
};
