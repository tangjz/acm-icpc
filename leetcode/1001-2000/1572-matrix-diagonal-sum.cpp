class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int n = mat.size(), ans = 0;
        for(int i = 0; i < n; ++i) {
            ans += mat[i][i];
            if(i != n - 1 - i)
                ans += mat[i][n - 1 - i];
        }
        return ans;
    }
};
