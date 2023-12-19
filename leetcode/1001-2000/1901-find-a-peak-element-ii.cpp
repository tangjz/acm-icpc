class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        auto get = [&](int x, int y) {
            return x < 0 || x >= n || y < 0 || y >= m ? -1 : mat[x][y];
        };
        if(n < m) {
            int yL = 0, yR = m - 1;
            while(yL < yR) {
                int yM = (yL + yR) >> 1;
                int xM = 0, best = get(xM, yM);
                for(int x = 1; x < n; ++x) {
                    int cur = get(x, yM);
                    if(cur > best) {
                        best = cur;
                        xM = x;
                    }
                }
                if(best < get(xM, yM - 1)) {
                    yR = yM - 1;
                } else if(best < get(xM, yM + 1)) {
                    yL = yM + 1;
                } else {
                    yL = yR = yM;
                }
            }
            int yM = yL;
            int xM = 0, best = get(xM, yM);
            for(int x = 1; x < n; ++x) {
                int cur = get(x, yM);
                if(cur > best) {
                    best = cur;
                    xM = x;
                }
            }
            return {xM, yM};
        } else {
            int xL = 0, xR = n - 1;
            while(xL < xR) {
                int xM = (xL + xR) >> 1;
                int yM = 0, best = get(xM, yM);
                for(int y = 1; y < m; ++y) {
                    int cur = get(xM, y);
                    if(cur > best) {
                        best = cur;
                        yM = y;
                    }
                }
                if(best < get(xM - 1, yM)) {
                    xR = xM - 1;
                } else if(best < get(xM + 1, yM)) {
                    xL = xM + 1;
                } else {
                    xL = xR = xM;
                }
            }
            int xM = xL;
            int yM = 0, best = get(xM, yM);
            for(int y = 1; y < m; ++y) {
                int cur = get(xM, y);
                if(cur > best) {
                    best = cur;
                    yM = y;
                }
            }
            return {xM, yM};
        }
    }
};
