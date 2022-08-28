class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        auto get = [&](int x, int y) {
            return x < 0 || x >= n || y < 0 || y >= m ? -1 : mat[x][y];
        };
        int xLen = n, xL = 0, xR = n - 1;
        int yLen = m, yL = 0, yR = m - 1;
        while(max(xLen, yLen) > 1)
            if(xLen < yLen) {
                int yM = (yL + yR) >> 1;
                int xM = xL, best = get(xM, yM);
                for(int x = xL + 1; x <= xR; ++x) {
                    int cur = get(x, yM);
                    if(cur > best) {
                        best = cur;
                        xM = x;
                    }
                }
                if(best < get(xM, yM - 1)) {
                    yR = yM - 1;
                    yLen = yR - yL + 1;
                } else if(best < get(xM, yM + 1)) {
                    yL = yM + 1;
                    yLen = yR - yL + 1;
                } else {
                    xLen = 1;
                    xL = xR = xM;
                    yLen = 1;
                    yL = yR = yM;
                }
            } else {
                int xM = (xL + xR) >> 1;
                int yM = yL, best = get(xM, yM);
                for(int y = yL + 1; y <= yR; ++y) {
                    int cur = get(xM, y);
                    if(cur > best) {
                        best = cur;
                        yM = y;
                    }
                }
                if(best < get(xM - 1, yM)) {
                    xR = xM - 1;
                    xLen = xR - xL + 1;
                } else if(best < get(xM + 1, yM)) {
                    xL = xM + 1;
                    xLen = xR - xL + 1;
                } else {
                    xLen = 1;
                    xL = xR = xM;
                    yLen = 1;
                    yL = yR = yM;
                }
            }
        return {xL, yL};
    }
};
