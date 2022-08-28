class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i < n / 2; ++i)
            for(int j = 0; j < (n + 1) / 2; ++j) {
                int x = i, y = j;
                for(int d = 0; d < 3; ++d) {
                    int xx = n - 1 - y, yy = x;
                    swap(matrix[x][y], matrix[xx][yy]);
                    tie(x, y) = {xx, yy};
                }
            }
    }
};
