class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        typedef long long LL;
        int n = grid[0].size();
        LL lft = 0, rht = 0;
        for(int i = 0; i < n; ++i)
            rht += grid[0][i];
        LL ans = LLONG_MAX;
        for(int i = 0; i < n; ++i) {
            rht -= grid[0][i];
            ans = min(ans, max(lft, rht));
            // printf("%d: %lld %lld\n", i, lft, rht);
            lft += grid[1][i];
        }
        return ans;
    }
};
