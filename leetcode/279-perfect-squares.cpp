class Solution {
public:
    int numSquares(int n) {
        int x = (int)ceil(sqrtl(n));
        for( ; x * x <= n; ++x);
        for( ; x * x > n; --x);
        if(x * x == n)
            return 1;
        for( ; !(n & 3); n >>= 2);
        if((n & 7) == 7)
            return 4;
        for(x = 2; x <= n; ++x) {
            if(x * x > n)
                x = n;
            if(n % x > 0)
                continue;
            int cnt;
            for(cnt = 1, n /= x; n % x == 0; ++cnt, n /= x);
            if((x & 3) == 3 && (cnt & 1))
                return 3;
        }
        return 2;
    }
};
