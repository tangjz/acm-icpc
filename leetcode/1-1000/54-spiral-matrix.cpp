class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        int r = (int)matrix.size();
        if(!r)
            return ret;
        int c = (int)matrix[0].size();
        int xL = 0, xR = r - 1, yL = 0, yR = c - 1;
        while(xL <= xR && yL <= yR) {
            for(int y = yL; y <= yR; ++y)
                ret.push_back(matrix[xL][y]);
            if((++xL) > xR)
                break;
            for(int x = xL; x <= xR; ++x)
                ret.push_back(matrix[x][yR]);
            if((--yR) < yL)
                break;
            for(int y = yR; y >= yL; --y)
                ret.push_back(matrix[xR][y]);
            if((--xR) < xL)
                break;
            for(int x = xR; x >= xL; --x)
                ret.push_back(matrix[x][yL]);
            ++yL;
        }
        return ret;
    }
};
