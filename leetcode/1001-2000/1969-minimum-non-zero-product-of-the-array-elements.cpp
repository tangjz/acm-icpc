class Solution {
public:
    int minNonZeroProduct(int p) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        LL n = 1LL << p;
        auto modPow = [&](int x, LL k) {
            int ret = 1;
            for(k %= mod - 1; k > 0; k >>= 1, x = (LL)x * x % mod)
                if(k & 1)
                    ret = (LL)ret * x % mod;
            return ret;
        };
        int m = n > 2 ? modPow((n - 2) % mod, n / 2 - 1) : 1;
        return (n - 1) % mod * m % mod;
    }
};
