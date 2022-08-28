class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& mat) {
        typedef long long LL;
        int r = mat.size(), c = mat[0].size();
        LL best = LLONG_MIN;
        vector<LL> vec(c);
        vector<int> out(4);
        for(int i = 0; i < r; ++i) {
            vec.assign(c, 0);
            for(int j = i; j < r; ++j) {
                LL pre = 0, cur = 0;
                for(int x = 0, y = -1; x < c; ++x) {
                    vec[x] += mat[j][x];
                    cur += vec[x];
                    if(best < cur - pre) {
                        best = cur - pre;
                        out = {i, y + 1, j, x};
                    }
                    if(pre > cur) {
                        pre = cur;
                        y = x;
                    }
                }
            }
        }
        return out;
    }
};
