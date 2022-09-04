class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        queue<pair<int, int> > que;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(mat[i][j]) {
                    mat[i][j] = -1;
                    continue;
                }
                que.push({i, j});
            }
        while(!que.empty()) {
            int ux, uy;
            tie(ux, uy) = que.front();
            que.pop();
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy;
                    if(vx < 0 || vx >= n || vy < 0 || vy >= m || mat[vx][vy] != -1)
                        continue;
                    mat[vx][vy] = mat[ux][uy] + 1;
                    que.push({vx, vy});
                }
        }
        return mat;
    }
};
