class Solution {
public:
    long long matrixSumQueries(int n, vector<vector<int>>& que) {
        typedef long long LL;
        int rc = 0, cc = 0;
        LL ans = 0;
        vector<bool> row(n), col(n);
        reverse(que.begin(), que.end());
        for(auto &it: que) {
            int typ = it[0], idx = it[1], val = it[2];
            if(!typ) {
                if(row[idx])
                    continue;
                ans += (LL)val * (n - cc);
                row[idx] = 1;
                ++rc;
            } else {
                if(col[idx])
                    continue;
                ans += (LL)val * (n - rc);
                col[idx] = 1;
                ++cc;
            }
        }
        return ans;
    }
};
