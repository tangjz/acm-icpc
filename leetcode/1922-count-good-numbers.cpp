class Solution {
    static const int mod = (int)1e9 + 7;
    int modPow(int x, long long k) {
        int ret = 1;
        for( ; k > 0; k >>= 1, x = 1LL * x * x % mod)
            if(k & 1)
                ret = 1LL * ret * x % mod;
        return ret;
    }
public:
    int countGoodNumbers(long long n) {
        return 1LL * modPow(5, (n + 1) >> 1) * modPow(4, n >> 1) % mod;
    }
};
