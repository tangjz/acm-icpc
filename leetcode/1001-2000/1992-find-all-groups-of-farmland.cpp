class Solution {
public:
    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        int n = land.size(), m = land[0].size();
        vector<vector<int> > ret;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(!land[i][j])
                    continue;
                if(i && land[i - 1][j])
                    continue;
                if(j && land[i][j - 1])
                    continue;
                int x = i, y = j;
                for( ; x < n && land[x][j]; ++x);
                for( ; y < m && land[i][y]; ++y);
                ret.push_back({i, j, x - 1, y - 1});
            }
        return ret;
    }
};
