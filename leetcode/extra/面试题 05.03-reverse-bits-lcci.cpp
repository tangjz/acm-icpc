class Solution {
public:
    int reverseBits(int num) {
        typedef unsigned long long ULL;
        int ret = 1, las = 0, cur;
        ULL x = (unsigned int)num;
        while(x > 0) {
            ULL p = x & -x;
            ULL y = (x + p) & ~x;
            cur = __builtin_ctzll(y / p);
            ret = max(ret, cur + 1 + (p == 1 ? las : 0));
            las = cur;
            x /= y << 1;
        }
        return min(ret, 32);
    }
};
