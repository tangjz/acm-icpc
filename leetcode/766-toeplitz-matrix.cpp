class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& mat) {
        int n = (int)mat.size(), m = (int)mat[0].size();
        unordered_map<int, int> Hash;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                int key = i - j;
                auto it = Hash.find(key);
                if(it == Hash.end())
                    it = Hash.insert({key, mat[i][j]}).first;
                if(mat[i][j] != it -> second)
                    return false;
            }
        return true;
    }
};
