class Solution {
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        vector<vector<int> > e(n);
        for(auto &it: paths) {
            e[it[0] - 1].push_back(it[1] - 1);
            e[it[1] - 1].push_back(it[0] - 1);
        }
        vector<int> col(n);
        for(int i = 0; i < n; ++i) {
            int msk = 0;
            for(int j: e[i])
                msk |= 1 << col[j];
            for(int j = 1; j <= 4; ++j)
                if(!((msk >> j) & 1)) {
                    col[i] = j;
                    break;
                }
        }
        return col;
    }
};
