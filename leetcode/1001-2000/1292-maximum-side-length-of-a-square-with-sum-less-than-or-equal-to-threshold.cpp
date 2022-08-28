class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int n = (int)mat.size(), m = (int)mat[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 1; j < m; ++j)
                mat[i][j] += mat[i][j - 1];
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < m; ++j)
                mat[i][j] += mat[i - 1][j];
        int L = 0, R = min(n, m);
        while(L < R) {
            int M = (L + R + 1) >> 1;
            bool chk = 0;
            auto get = [&](int x, int y) {
                return x >= 0 && y >= 0 ? mat[x][y] : 0;
            };
            auto area = [&](int x1, int y1, int x2, int y2) {
                return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
            };
            for(int i = M; !chk && i <= n; ++i)
                for(int j = M; !chk && j <= m; ++j)
                    chk |= area(i - M, j - M, i - 1, j - 1) <= threshold;
            if(chk) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
