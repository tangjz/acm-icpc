class Solution {
public:
    double myPow(double x, int n) {
        double ret = 1;
        for( ; n < 0; n /= 2, x = x * x)
            if(n & 1)
                ret = ret * x;
        ret = 1 / ret;
        for( ; n > 0; n >>= 1, x = x * x)
            if(n & 1)
                ret = ret * x;
        return ret;
    }
};
