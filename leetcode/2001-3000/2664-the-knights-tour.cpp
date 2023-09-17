class Solution {
public:
    vector<vector<int>> tourOfKnight(int m, int n, int r, int c) {
        static const int maxd = 8, dx[] = {-2, -2, -1, -1, 1, 1, 2, 2}, dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
        int sz = m * n;
        vector<vector<int> > pos(m, vector<int>(n, -1));
        function<bool(int, int)> dfs = [&](int x, int y) {
            if(pos[x][y] == sz - 1)
                return 1;
            for(int i = 0; i < 8; ++i) {
                int xx = x + dx[i], yy = y + dy[i];
                if(xx < 0 || xx >= m || yy < 0 || yy >= n || pos[xx][yy] != -1)
                    continue;
                pos[xx][yy] = pos[x][y] + 1;
                if(dfs(xx, yy))
                    return 1;
                pos[xx][yy] = -1;
            }
            return 0;
        };
        pos[r][c] = 0;
        dfs(r, c);
        return pos;
    }
};
