class Solution {
public:
    long long distributeCandies(int n, int limit) {
        typedef long long LL;
        auto binom = [&](int n, int m) -> LL {
            if(n < m)
                return 0;
            LL prd = 1;
            for(int i = 1; i <= m; ++i)
                prd = prd * (n + 1 - i) / i;
            return prd;
        };
        LL ans = 0;
        for(int i = 0; i <= 3; ++i)
            ans += (i & 1 ? -1 : 1) * binom(3, i) * binom(n - (limit + 1) * i + 2, 2);
        return ans;
    }
};
