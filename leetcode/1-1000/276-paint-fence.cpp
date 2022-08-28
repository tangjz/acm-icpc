class Solution {
public:
    int numWays(int n, int k) {
        typedef long long LL;
        vector<pair<int, int> > f(n + 1);
        f[0] = {0, 1};
        for(int i = 1; i <= n; ++i) {
            f[i].first = f[i - 1].second - (i >= 3 ? f[i - 3].second - f[i - 3].first : 0);
            f[i].second = f[i].first * k;
            // printf("%d: %d %d\n", i, f[i].first, f[i].second);
        }
        return f.back().second;
    }
};
