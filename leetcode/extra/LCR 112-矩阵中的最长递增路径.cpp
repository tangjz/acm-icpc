class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int r = (int)matrix.size();
        if(!r)
            return 0;
        int c = (int)matrix[0].size();
        vector<vector<int> > dist(r, vector<int>(c, 0));
        auto is_valid = [&](int x, int y) {
            return x >= 0 && x < r && y >= 0 && y < c;
        };
        function<int(int, int)> dfs = [&](int x, int y) {
            int &ret = dist[x][y];
            if(!ret) {
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy)
                        if(!dx != !dy) {
                            int xx = x + dx, yy = y + dy;
                            if(is_valid(xx, yy) && matrix[x][y] < matrix[xx][yy])
                                ret = max(ret, dfs(xx, yy));
                        }
                ++ret;
            }
            return ret;
        };
        int ans = 0;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                ans = max(ans, dfs(i, j));
        return ans;
    }
};
