class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int r = (int)grid.size();
        if(!r)
            return 0;
        int c = (int)grid[0].size();
        if(!c)
            return 0;
        const int INF = ~0U >> 1;
        vector<int> ans = grid[0];
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(!i && !j)
                    continue;
                int adt = INF;
                if(i > 0)
                    adt = min(adt, ans[j]);
                if(j > 0)
                    adt = min(adt, ans[j - 1]);
                ans[j] = grid[i][j] + adt;
            }
        return ans.back();
    }
};
