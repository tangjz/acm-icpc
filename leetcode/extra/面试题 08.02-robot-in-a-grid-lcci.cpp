class Solution {
public:
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size(), n = r * c;
        vector<bool> can(n);
        for(int i = r - 1, idx = n - 1; i >= 0; --i)
            for(int j = c - 1; j >= 0; --j, --idx) {
                if(mat[i][j])
                    continue;
                if(idx == n - 1)
                    can[idx] = 1;
                if(i + 1 < r && can[idx + c])
                    can[idx] = 1;
                if(j + 1 < c && can[idx + 1])
                    can[idx] = 1;
            }
        if(!can[0])
            return {};
        vector<vector<int> > path;
        for(int idx = 0, i = 0, j = 0; idx < n - 1; ) {
            path.push_back({i, j});
            if(i + 1 < r && can[idx + c]) {
                ++i;
                idx += c;
            } else {
                ++j;
                ++idx;
            }
        }
        path.push_back({r - 1, c - 1});
        return path;
    }
};
