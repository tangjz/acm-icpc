class Solution {
public:
    int findChampion(vector<vector<int>>& grid) {
        int n = grid.size();
        for(int i = 0; i < n; ++i) {
            int deg = 0;
            for(int j = 0; j < n; ++j)
                deg += i != j && !grid[i][j];
            if(!deg)
                return i;
        }
        return -1;
    }
};
