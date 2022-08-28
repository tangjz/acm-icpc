class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& pre, vector<vector<int>>& que) {
        vector<vector<int> > e(n, vector<int>(n, 0));
        for(auto &it : pre)
            e[it[0]][it[1]] = 1;
        for(int i = 0; i < n; ++i)
            e[i][i] = 1;
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i) if(e[i][k])
                for(int j = 0; j < n; ++j) if(e[k][j])
                    e[i][j] = 1;
        int m = (int)que.size(), pos = 0;
        vector<bool> ret(m, 0);
        for(auto &it : que) {
            ret[pos] = e[it[0]][it[1]] == 1;
            ++pos;
        }
        return ret;
    }
};
