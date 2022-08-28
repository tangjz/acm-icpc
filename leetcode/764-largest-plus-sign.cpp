class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        static const int maxn = 501, dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
        int ans = 0;
        static bool mat[maxn][maxn];
        static int dp[5][maxn][maxn];
        for(int i = 0; i < n; ++i) {
            memset(mat[i], true, n * sizeof(bool));
            for(int j = 0; j < 4; ++j)
                memset(dp[j][i], 0, n * sizeof(int));
        }
        for(auto &it: mines)
            mat[it[0]][it[1]] = false;
        function<int(int, int, int)> calc = [&](int d, int x, int y) {
            if(x < 0 || x >= n || y < 0 || y >= n || !mat[x][y])
                return 0;
            int &ret = dp[d][x][y];
            if(!ret)
                ret = 1 + calc(d, x + dx[d], y + dy[d]);
            return ret;
        };
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                int tmp = INT_MAX;
                for(int d = 0; d < 4; ++d)
                    tmp = min(tmp, calc(d, i, j));
                ans = max(ans, tmp);
            }
        return ans;
    }
};
