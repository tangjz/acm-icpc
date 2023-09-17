class Solution {
public:
    vector<int> findColumnWidth(vector<vector<int>>& grid) {
        int c = grid[0].size();
        vector<int> ret(c);
        for(auto &row: grid)
            for(int i = 0; i < c; ++i)
                ret[i] = max(ret[i], (int)to_string(row[i]).size());
        return ret;
    }
};
