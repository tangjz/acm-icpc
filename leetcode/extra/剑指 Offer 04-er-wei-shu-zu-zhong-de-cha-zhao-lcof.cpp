class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int n = matrix.size(), m = n ? matrix[0].size() : 0;
        if(!m)
            return false;
        for(int i = 0, j = m - 1; i < n; ++i) {
            for( ; j >= 0 && matrix[i][j] > target; --j);
            if(j >= 0 && matrix[i][j] == target)
                return true;
        }
        return false;
    }
};
