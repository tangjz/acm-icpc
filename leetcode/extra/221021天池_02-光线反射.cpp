class Solution {
public:
    int getLength(vector<string>& grid) {
        const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        int r = grid.size(), c = grid[0].size();
        int ans = 0, x = 0, y = 0, d = 1;
        while(x >= 0 && x < r && y >= 0 && y < c) {
            ++ans;
            if(grid[x][y] == 'L') {
                d ^= 1;
            } else if(grid[x][y] == 'R') {
                d ^= 3;
            }
            x += dx[d];
            y += dy[d];
        }
        return ans;
    }
};
