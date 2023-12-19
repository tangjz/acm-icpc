class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int n = grid.size(), m = n * n;
        vector<int> ctr(m + 1);
        for(auto &row: grid)
            for(int x: row)
                ++ctr[x];
        int a = -1, b = -1;
        for(int i = 1; i <= m; ++i)
            if(!ctr[i]) {
                b = i;
            } else if(ctr[i] > 1) {
                a = i;
            }
        return {a, b};
    }
};
