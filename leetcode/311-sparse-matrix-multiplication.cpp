class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        int a = mat1.size(), b = mat2.size(), c = mat2[0].size();
        vector<vector<pair<int, int> > > row(a), col(c);
        for(int i = 0; i < a; ++i)
            for(int j = 0; j < b; ++j)
                if(mat1[i][j])
                    row[i].push_back({j, mat1[i][j]});
        for(int j = 0; j < b; ++j)
            for(int k = 0; k < c; ++k)
                if(mat2[j][k])
                    col[k].push_back({j, mat2[j][k]});
        vector<vector<int> > ret(a, vector<int>(c));
        for(int i = 0; i < a; ++i)
            for(int j = 0; j < c; ++j) {
                int &res = ret[i][j];
                for(auto it = row[i].begin(), jt = col[j].begin(); it != row[i].end() && jt != col[j].end(); )
                    if(it -> first == jt -> first) {
                        res += it -> second * jt -> second;
                        ++it;
                        ++jt;
                    } else if(it -> first < jt -> first) {
                        ++it;
                    } else {
                        ++jt;
                    }
            }
        return ret;
    }
};
