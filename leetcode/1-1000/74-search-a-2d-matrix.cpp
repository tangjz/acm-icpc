class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size(), m = matrix[0].size();
        for(int i = 0, j = m - 1; i < n; ++i) {
            for( ; j >= 0 && matrix[i][j] > target; --j);
            if(j >= 0 && matrix[i][j] == target)
                return true;
        }
        return false;
    }
};
