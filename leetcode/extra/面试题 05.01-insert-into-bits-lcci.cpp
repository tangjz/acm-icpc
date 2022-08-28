class Solution {
public:
    int insertBits(int N, int M, int i, int j) {
        int len = j - i + 1;
        unsigned int u = N, v = M;
        v ^= u >> i;
        if(len < 32)
            v &= (1 << len) - 1;
        u ^= v << i;
        return u;
    }
};
