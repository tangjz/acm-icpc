class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        static pair<int, int> A[9], B[9];
        static int e[9][9], dp[1 << 9 | 1] = {}, bits[1 << 9 | 1] = {};
        if(!bits[1]) {
            for(int i = 1; i < (1 << 9); ++i)
                bits[i] = bits[i >> 1] + (i & 1);
        }
        for(int i = 0, cA = 0, cB = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j) {
                A[cA++] = {i, j};
                for(int k = 0; k < grid[i][j]; ++k)
                    B[cB++] = {i, j};
            }
        for(int i = 0; i < 9; ++i)
            for(int j = 0; j < 9; ++j)
                e[i][j] = abs(A[i].first - B[j].first) + abs(A[i].second - B[j].second);
        for(int s = 1; s < (1 << 9); ++s) {
            int i = bits[s] - 1;
            dp[s] = INT_MAX;
            for(int j = 0; j < 9; ++j)
                if((s >> j) & 1)
                    dp[s] = min(dp[s], dp[s ^ (1 << j)] + e[i][j]);
        }
        return dp[(1 << 9) - 1];
    }
};
