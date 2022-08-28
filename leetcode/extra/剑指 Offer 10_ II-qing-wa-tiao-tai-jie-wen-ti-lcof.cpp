class Solution {
public:
    int numWays(int n) {
        static const int maxn = 103, mod = (int)1e9 + 7;
        static int m = 2, fib[maxn] = {0, 1, 1};
        for( ; m <= n; ++m)
            (fib[m + 1] = fib[m] + fib[m - 1]) >= mod && (fib[m + 1] -= mod);
        return fib[n + 1];
    }
};
