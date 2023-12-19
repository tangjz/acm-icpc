class Solution {
public:
    int maximumXorProduct(long long a, long long b, int n) {
        typedef long long LL;
        LL msk = 0, las = 0;
        for(int i = 0; i < n; ++i) {
            LL u = (a >> i) & 1;
            LL v = (b >> i) & 1;
            if(u != v) {
                las = 1LL << i;
                msk |= las;
                a ^= u << i;
                b ^= v << i;
            } else if(!u) {
                a |= 1LL << i;
                b |= 1LL << i;
            }
        }
        const int mod = (int)1e9 + 7;
        if(a == b)
            return (a + las) % mod * ((b + msk - las) % mod) % mod;
        if(a > b)
            swap(a, b);
        return (a + msk) % mod * (b % mod) % mod;
    }
};
