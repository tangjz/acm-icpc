class Solution {
public:
    int maxSum(vector<vector<int>>& grid) {
        int ans = 0, r = grid.size(), c = grid[0].size();
        for(int i = 0; i <= r - 3; ++i)
            for(int j = 0; j <= c - 3; ++j) {
                int sum = 0;
                for(int x = 0; x < 3; ++x)
                    for(int y = 0; y < 3; ++y)
                        sum += grid[i + x][j + y];
                sum -= grid[i + 1][j] + grid[i + 1][j + 2];
                ans = max(ans, sum);
            }
        return ans;
    }
};
