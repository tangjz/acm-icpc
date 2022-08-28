class Solution {
public:
    vector<vector<int>> minScore(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<pair<int, int> > que(n);
        for(int i = 0; i < n; ++i)
            que[i] = {i / c, i % c};
        // distinct
        sort(que.begin(), que.end(), [&](auto const &u, auto const &v) {
            return grid[u.first][u.second] < grid[v.first][v.second];
        });
        vector<int> row(r), col(c);
        for(auto &it: que) {
            int x, y;
            tie(x, y) = it;
            grid[x][y] = max(row[x], col[y]) + 1;
            row[x] = col[y] = grid[x][y];
        }
        return grid;
    }
};
