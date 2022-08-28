class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int n = (int)grid.size();
        if(!n)
            return 0;
        int m = (int)grid[0].size(), ret = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(!grid[i][j])
                    continue;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        int x = i + dx, y = j + dy;
                        ret += x < 0 || x >= n || y < 0 || y >= m || !grid[x][y];
                    }
            }
        return ret;
    }
};
