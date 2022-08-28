class Solution {
public:
    int electricityExperiment(int row, int col, vector<vector<int>>& position) {
        vector<vector<vector<int> > > mat(1, vector<vector<int> >(row, vector<int>(row)));
        for(int i = 0; i < row; ++i) {
            if(i > 0)
                mat[0][i][i - 1] = 1;
            mat[0][i][i] = 1;
            if(i + 1 < row)
                mat[0][i][i + 1] = 1;
        }
        for(auto &it: position)
            swap(it[0], it[1]);
        sort(position.begin(), position.end());
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        auto mul = [&](vector<vector<int> > &lft, vector<vector<int> > &rht) -> vector<vector<int> > {
            int r = lft.size(), m = lft[0].size(), c = rht[0].size();
            vector<vector<int> > ret(r, vector<int>(c));
            for(int i = 0; i < r; ++i)
                for(int j = 0; j < m; ++j)
                    for(int k = 0; k < c; ++k)
                        ret[i][k] = (ret[i][k] + (LL)lft[i][j] * rht[j][k]) % mod;
            return ret;
        };
        int ans = 1;
        while(position.size() > 1 && ans) {
            int dt = position.back()[0], sta = position.back()[1];
            position.pop_back();
            int end = position.back()[1];
            dt -= position.back()[0];
            vector<vector<int> > vec(1, vector<int>(row));
            vec[0][sta] = 1;
            for(int i = 0; dt > 0; ++i, dt >>= 1) {
                if(!(dt & 1))
                    continue;
                while(i >= mat.size())
                    mat.push_back(mul(mat.back(), mat.back()));
                vec = mul(vec, mat[i]);
            }
            ans = (LL)ans * vec[0][end] % mod;
        }
        return ans;
    }
};
