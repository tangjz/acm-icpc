class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int r = image.size(), c = image[0].size();
        int xL, xR, yL, yR;
        for(int L = 0, M, &R = xL = x; L < R; ) {
            M = (L + R) >> 1;
            bool found = 0;
            for(int i = 0; !found && i < c; ++i)
                found |= image[M][i] == '1';
            if(found) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        for(int &L = xR = x, M, R = r - 1; L < R; ) {
            M = (L + R + 1) >> 1;
            bool found = 0;
            for(int i = 0; !found && i < c; ++i)
                found |= image[M][i] == '1';
            if(found) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        for(int L = 0, M, &R = yL = y; L < R; ) {
            M = (L + R) >> 1;
            bool found = 0;
            for(int i = 0; !found && i < r; ++i)
                found |= image[i][M] == '1';
            if(found) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        for(int &L = yR = y, M, R = c - 1; L < R; ) {
            M = (L + R + 1) >> 1;
            bool found = 0;
            for(int i = 0; !found && i < r; ++i)
                found |= image[i][M] == '1';
            if(found) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return (xR - xL + 1) * (yR - yL + 1);
    }
};
