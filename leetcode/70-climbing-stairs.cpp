class Solution {
public:
    int climbStairs(int n) {
        static const int maxn = 47;
        static int m = 2, fib[maxn] = {0, 1, 1};
        for( ; m <= n; ++m)
            fib[m + 1] = fib[m] + fib[m - 1];
        return fib[n + 1];
    }
};
