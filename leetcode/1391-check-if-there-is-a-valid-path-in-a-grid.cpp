class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        const int d[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        const int msk[] = {0, 2 + 8, 1 + 4, 4 + 8, 2 + 4, 1 + 8, 1 + 2};
        int r = (int)grid.size(), c = (int)grid[0].size();
        vector<vector<vector<int> > > e(r, vector<vector<int> >(c, vector<int>()));
        auto isValid = [&](int x, int y) -> bool {
            return x >= 0 && x < r && y >= 0 && y < c;
        };
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                for(int o = 0; o < 4; ++o) {
                    if(!((msk[grid[i][j]] >> o) & 1))
                        continue;
                    int x = i + d[o][0], y = j + d[o][1];
                    if(isValid(x, y) && (msk[grid[x][y]] >> (o ^ 2)) & 1)
                        e[i][j].push_back(o);
                }
            }
        vector<vector<char> > vis(r, vector<char>(c, 0));
        queue<pair<int, int> > que;
        auto append = [&](int x, int y) -> void {
            if(isValid(x, y) && !vis[x][y]) {
                vis[x][y] = 1;
                que.push(make_pair(x, y));
            }
        };
        append(0, 0);
        while(!vis[r - 1][c - 1] && !que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            for(int o : e[x][y])
                append(x + d[o][0], y + d[o][1]);
        }
        return vis[r - 1][c - 1];
    }
};
