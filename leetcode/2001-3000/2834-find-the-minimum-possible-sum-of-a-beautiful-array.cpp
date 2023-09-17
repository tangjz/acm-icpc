class Solution {
public:
    long long minimumPossibleSum(int n, int m) {
        typedef long long LL;
        int rem = n;
        LL ans = 0;
        for(int i = 1, j = m - 1; rem > 0 && i <= j; ++i, --j) {
            ans += i;
            --rem;
        }
        for(int i = m; rem > 0; ++i) {
            ans += i;
            --rem;
        }
        return ans;
    }
};
