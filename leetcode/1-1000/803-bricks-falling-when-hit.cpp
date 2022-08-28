class Solution {
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int r = grid.size(), c = grid[0].size(), cnt = 0;
        vector<vector<int> > rem(r, vector<int>(c));
        vector<vector<bool> > vis(r, vector<bool>(c));
        queue<pair<int, int> > que;
        vector<int> ans;
        for(auto &it: hits)
            ++rem[it[0]][it[1]];
        auto upd = [&](int x, int y) {
            if(x < 0 || x >= r || y < 0 || y >= c || vis[x][y])
                return;
            if(rem[x][y] || !grid[x][y])
                return;
            if(x > 0) {
                bool ban = 1;
                for(int dx = -1; ban && dx <= 1; ++dx)
                    for(int dy = -1; ban && dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        int xx = x + dx, yy = y + dy;
                        if(xx < 0 || xx >= r || yy < 0 || yy >= c || !vis[xx][yy])
                            continue;
                        ban = 0;
                    }
                if(ban)
                    return;
            }
            ++cnt;
            vis[x][y] = 1;
            que.push({x, y});
        };
        auto parse = [&]() {
            while(!que.empty()) {
                int x, y;
                tie(x, y) = que.front();
                que.pop();
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        int xx = x + dx, yy = y + dy;
                        if(xx < 0 || xx >= r || yy < 0 || yy >= c || vis[xx][yy])
                            continue;
                        if(rem[xx][yy] || !grid[xx][yy])
                            continue;
                        ++cnt;
                        vis[xx][yy] = 1;
                        que.push({xx, yy});
                    }
            }
        };
        for(int i = 0; i < c; ++i)
            upd(0, i);
        parse();
        while(!hits.empty()) {
            int x = hits.back()[0], y = hits.back()[1];
            --rem[x][y];
            upd(x, y);
            int oldCnt = cnt;
            parse();
            ans.push_back(cnt - oldCnt);
            hits.pop_back();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
