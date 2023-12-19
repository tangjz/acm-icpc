class Solution {
public:
    int distributeCandies(int n, int limit) {
        typedef long long LL;
        auto binom = [&](int n, int m) -> LL {
            if(n < m)
                return 0;
            if(!m)
                return 1;
            if(m == 1)
                return n;
            if(m == 2)
                return n * (n - 1LL) / 2;
            if(m == 3)
                return n * (n - 1LL) * (n - 2) / 6;
            return INT_MAX;
        };
        LL ans = 0;
        for(int i = 0; i <= 3; ++i) {
            // (-1)^i C(3, i) C(n-i*(limit+1), 3)
            ans += (i & 1 ? -1 : 1) * binom(3, i) * binom(n - i * (limit + 1) + 2, 2);
        }
        return ans;
    }
};
