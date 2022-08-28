class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        int sta = 0;
        for(auto &row: mat) {
            sort(row.begin(), row.end());
            sta += row.front();
        }
        int n = mat.size(), m = mat[0].size();
        if(k == 1) {
            return sta;
        }
        // m > 1
        sort(mat.begin(), mat.end(), [&](auto const &it, auto const &jt) {
            return it[1] - it[0] < jt[1] - jt[0];
        });
        multiset<vector<int> > que;
        que.insert({sta, 0, 0, 0});
        for(int i = 1; i < k; ++i) {
            vector<int> cur = *que.begin();
            que.erase(que.begin());
            int val = cur[0], x = cur[1], y = cur[2], z = cur[3];
            // printf("#%d: %d %d %d %d %d\n", i, val, x, y, z);
            if(y + 1 < m)
                que.insert({val - mat[x][y] + mat[x][y + 1], x, y + 1, 0});
            if(x + 1 < n) {
                que.insert({val - mat[x + 1][0] + mat[x + 1][1], x + 1, 1, 1});
                if(z == 1) {
                    que.insert({val - mat[x][1] + mat[x][0] - mat[x + 1][0] + mat[x + 1][1], x + 1, 1, 1});
                }
            }
        }
        return que.begin() -> front();
    }
};
