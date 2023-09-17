class Solution {
public:
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), sz = 1 << n;
        vector<vector<int> > pos(sz);
        for(int i = 0; i < m; ++i) {
            int msk = 0;
            for(int x: grid[i])
                msk = msk << 1 | x;
            pos[msk].push_back(i);
        }
        vector<int> vals;
        if(!pos[0].empty())
            return pos[0];
        for(int i = 1; i < sz; ++i) {
            if(pos[i].empty())
                continue;
            for(int j = i + 1; j < sz; ++j)
                if(!(i & j) && !pos[j].empty()) {
                    vector<int> ret = {pos[i].front(), pos[j].front()};
                    if(ret[0] > ret[1])
                        swap(ret[0], ret[1]);
                    return ret;
                }
        }
        return {};
    }
};
