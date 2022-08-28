class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), ans = 0;
        for(int i = 0; i <= r - 3; ++i)
            for(int j = 0; j <= c - 3; ++j) {
                int sum[8] = {};
                bool ban = 0, vis[9] = {};
                for(int x = 0; !ban && x < 3; ++x)
                    for(int y = 0; !ban && y < 3; ++y) {
                        int v = grid[i + x][j + y];
                        if(v <= 0 || v > 9 || vis[v - 1]) {
                            ban = 1;
                            break;
                        }
                        vis[v - 1] = 1;
                        sum[x] += v;
                        sum[3 + y] += v;
                        if(x == y)
                            sum[6] += v;
                        if(x + y == 2)
                            sum[7] += v;
                    }
                for(int k = 1; !ban && k < 8; ++k)
                    ban |= sum[k] != sum[0];
                ans += !ban;
            }
        return ans;
    }
};
