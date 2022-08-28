class Solution {
public:
    int maxValue(vector<vector<int>>& e, int m) {
        int n = (int)e.size();
        sort(e.begin(), e.end(), [&](auto const &u, auto const &v) {
            return u[1] < v[1];
        });
        vector<int> rht;
        for(auto &it : e)
            rht.push_back(it[1]);
        // dp(i, j): events[0..i] has j
        // dp(i, j) = dp(i-1,j) or dp(t,j-1)
        typedef long long LL;
        static const int maxv = (int)2e6 + 9;
        static LL pool[maxv];
        function<LL&(int, int)> dp = [&](int i, int j) -> LL& {
            return pool[i * (m + 1) + j];
        };
        function<void(LL &, LL)> getMax = [&](LL &x, LL y) -> void {
            x < y && (x = y);
        };
        for(int i = 0; i <= m; ++i)
            dp(0, i) = 0;
        for(int i = 0; i < n; ++i) {
            int t = lower_bound(rht.begin(), rht.end(), e[i][0]) - rht.begin();
            for(int j = 0; j <= m; ++j) {
                dp(i + 1, j) = dp(i, j);
                if(j > 0)
                    getMax(dp(i + 1, j), dp(t, j - 1) + e[i][2]);
            }
        }
        return dp(n, m);
    }
};
