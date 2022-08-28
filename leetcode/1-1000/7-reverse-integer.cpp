class Solution {
public:
    int reverse(int x) {
        unsigned int y = x < 0 ? ~(unsigned int)x + 1 : x;
        unsigned int z = 0;
        for( ; y > 0; y /= 10) {
            unsigned int r = y % 10;
            if(z > (UINT_MAX - r) / 10)
                return 0;
            z = z * 10 + r;
        }
        if(z > (1UL << 31) - (x > 0))
            return 0;
        if(x < 0)
            z = ~z + 1;
        return (int)z;
    }
};
