class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int n = (int)grid.size(), m = (int)grid[0].size();
        vector<int> seq;
        seq.reserve(n * m);
        for(auto &it : grid)
            for(int x : it)
                seq.push_back(x);
        k %= n * m;
        k > 0 && (k = n * m - k);
        rotate(seq.begin(), seq.begin() + k, seq.end());
        int pos = 0;
        for(auto &it : grid)
            for(int &x : it)
                x = seq[pos++];
        return grid;
    }
};
