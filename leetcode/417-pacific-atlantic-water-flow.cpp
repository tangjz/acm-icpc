class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        vector<vector<int> > msk(n, vector<int>(m)), ret;
        for(int t = 0; t < 2; ++t) {
            int v = 1 << t;
            queue<pair<int, int> > que;
            if(t == 0) {
                for(int i = 0; i < m; ++i) {
                    msk[0][i] |= v;
                    que.push({0, i});
                }
                for(int i = 1; i < n; ++i) {
                    msk[i][0] |= v;
                    que.push({i, 0});
                }
            } else {
                for(int i = 0; i < m; ++i) {
                    msk[n - 1][i] |= v;
                    que.push({n - 1, i});
                }
                for(int i = 0; i < n - 1; ++i) {
                    msk[i][m - 1] |= v;
                    que.push({i, m - 1});
                }
            }
            while(!que.empty()) {
                int x, y;
                tie(x, y) = que.front();
                que.pop();
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        int xx = x + dx, yy = y + dy;
                        if(xx < 0 || xx >= n || yy < 0 || yy >= m || (msk[xx][yy] & v) || heights[xx][yy] < heights[x][y])
                            continue;
                        msk[xx][yy] |= v;
                        que.push({xx, yy});
                    }
            }
        }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(msk[i][j] == 3)
                    ret.push_back({i, j});
        return ret;
    }
};
