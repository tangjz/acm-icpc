class Solution {
public:
    bool checkValidGrid(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<pair<int, int> > seq(n);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                seq[grid[i][j]] = {i, j};
        if(seq[0].first || seq[0].second)
            return 0;
        for(int i = 1; i < n; ++i) {
            int dx = abs(seq[i].first - seq[i - 1].first);
            int dy = abs(seq[i].second - seq[i - 1].second);
            if(dx > dy)
                swap(dx, dy);
            if(!(dx == 1 && dy == 2))
                return 0;
        }
        return 1;
    }
};
