class Solution {
public:
    bool isPossibleToCutPath(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size();
        vector<vector<int> > msk(r, vector<int>(c));
        mat[0][0] = mat[r - 1][c - 1] = -1;
        for(int i = 0; i < 2; ++i) {
            queue<pair<int, int> > que;
            auto upd = [&](int x, int y) {
                if(x < 0 || x >= r || y < 0 || y >= c || mat[x][y] || msk[x][y] & (1 << i))
                    return;
                msk[x][y] |= 1 << i;
                que.push({x, y});
            };
            for(int x = 0; x < r; ++x)
                upd(x, i ? 0 : c - 1);
            for(int y = 0; y < c; ++y)
                upd(i ? r - 1 : 0, y);
            while(!que.empty()) {
                int x, y;
                tie(x, y) = que.front();
                que.pop();
                if(msk[x][y] == 3)
                    return 1;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy)
                        upd(x + dx, y + dy);
            }
        }
        for(int x = 0; x < r; ++x)
            for(int y = 0; y < c; ++y) {
                if(mat[x][y] != 1)
                    continue;
                int agg = (!x || y == c - 1) | (x == r - 1 || !y) << 1;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        int xx = x + dx, yy = y + dy;
                        if(xx < 0 || xx >= r || yy < 0 || yy >= c)
                            continue;
                        agg |= msk[xx][yy];
                    }
                if(agg == 3)
                    return 1;
            }
        return 0;
    }
};
