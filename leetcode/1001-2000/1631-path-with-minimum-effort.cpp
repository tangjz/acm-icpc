class Solution {
    bool check(vector<vector<int>>& mat, int diff) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<bool> > vis(n, vector<bool>(m));
        queue<pair<int, int> > que;
        auto upd = [&](int x, int y, int v) {
            if(x < 0 || x >= n || y < 0 || y >= m || vis[x][y] || abs(v - mat[x][y]) > diff)
                return;
            vis[x][y] = 1;
            que.push({x, y});
        };
        upd(0, 0, mat[0][0]);
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            if(x == n - 1 && y == m - 1)
                return true;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!!dx == !!dy)
                        continue;
                    upd(x + dx, y + dy, mat[x][y]);
                }
        }
        return false;
    }
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int L = 0, R = (int)1e6;
        while(L < R) {
            int M = (L + R) >> 1;
            if(check(heights, M)) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
