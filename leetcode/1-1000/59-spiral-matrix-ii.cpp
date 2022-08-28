class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int> > mat(n, vector<int>(n));
        int x = 0, y = 0, dx = 0, dy = 1, idx = 0;
        mat[x][y] = ++idx;
        for(bool upd = true; upd; tie(dx, dy) = make_pair(dy, -dx)) {
            upd = false;
            while(true) {
                int xx = x + dx, yy = y + dy;
                if(xx >= 0 && xx < n && yy >= 0 && yy < n && !mat[xx][yy]) {
                    mat[xx][yy] = ++idx;
                    tie(x, y) = make_pair(xx, yy);
                    upd = true;
                } else {
                    break;
                }
            }
        }
        return mat;
    }
};
