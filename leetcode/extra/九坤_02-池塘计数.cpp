class Solution {
public:
    int lakeCount(vector<string>& mat) {
        int ans = 0, r = mat.size(), c = mat[0].size();
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(mat[i][j] != 'W')
                    continue;
                ++ans;
                queue<pair<int, int> > que;
                mat[i][j] = '.';
                que.push({i, j});
                while(!que.empty()) {
                    int x, y;
                    tie(x, y) = que.front();
                    que.pop();
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            int xx = x + dx, yy = y + dy;
                            if(xx < 0 || xx >= r || yy < 0 || yy >= c || mat[xx][yy] != 'W')
                                continue;
                            mat[xx][yy] = '.';
                            que.push({xx, yy});
                        }
                }
            }
        return ans;
    }
};
