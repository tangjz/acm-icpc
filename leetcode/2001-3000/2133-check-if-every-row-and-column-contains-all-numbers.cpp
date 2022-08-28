class Solution {
public:
    bool checkValid(vector<vector<int>>& mat) {
        int n = mat.size();
        for(int i = 0; i < n; ++i) {
            vector<int> ctr(n);
            for(int j = 0; j < n; ++j) {
                int v = mat[i][j] - 1;
                if(ctr[v])
                    return false;
                ctr[v] = 1;
            }
        }
        for(int i = 0; i < n; ++i) {
            vector<int> ctr(n);
            for(int j = 0; j < n; ++j) {
                int v = mat[j][i] - 1;
                if(ctr[v])
                    return false;
                ctr[v] = 1;
            }
        }
        return true;
    }
};
