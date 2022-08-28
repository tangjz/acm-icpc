class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = (int)matrix.size(), L = matrix[0][0], R = matrix[n - 1][n - 1];
        while(L < R) {
            int M = L + (R - L) / 2, upp = L - 1, cnt = 0;
            for(int i = 0, j = n - 1; i < n; ++i) {
                for( ; j >= 0 && matrix[i][j] > M; --j);
                if(j < 0)
                    break;
                cnt += j + 1;
                upp = max(upp, matrix[i][j]);
            }
            if(cnt < k) {
                L = M + 1;
            } else {
                R = upp;
            }
        }
        return R;
    }
};
