class Solution {
public:
    int divide(int dividend, int divisor) {
        int x = dividend, y = divisor;
        if(x == INT_MIN && y == -1)
            return INT_MAX;
        if(y == INT_MIN)
            return x == INT_MIN;
        int ret = 0, sgn = 1;
        if(y < 0) {
            y = -y;
            sgn = -sgn;
        }
        if(x == INT_MIN) {
            x += y;
            ret -= sgn;
        }
        if(x < 0) {
            x = -x;
            sgn = -sgn;
        }
        int mx = 0;
        for( ; y <= (x >> mx); ++mx);
        for(int i = mx - 1; i >= 0; --i)
            if((x >> i) >= y) {
                x -= y << i;
                ret += sgn * (1 << i);
            }
        return ret;
    }
};
