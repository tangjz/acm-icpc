class Solution {
public:
    int maxIncreasingCells(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size(), n = r * c, ans = 0;
        vector<int> dp(n), row(r), col(c);
        vector<pair<int, int> > ord(n);
        for(int i = 0, k = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                ord[k++] = {i, j};
        sort(ord.begin(), ord.end(), [&](auto const &u, auto const &v) {
            return mat[u.first][u.second] > mat[v.first][v.second];
        });
        for(int i = 0, j; i < n; ) {
            int v = mat[ord[i].first][ord[i].second];
            for(j = i; j < n && mat[ord[j].first][ord[j].second] == v; ++j) {
                int p = ord[j].first * c + ord[j].second;
                dp[p] = max(row[ord[j].first], col[ord[j].second]) + 1;
                ans = max(ans, dp[p]);
            }
            for( ; i < j; ++i) {
                int p = ord[i].first * c + ord[i].second;
                row[ord[i].first] = max(row[ord[i].first], dp[p]);
                col[ord[i].second] = max(col[ord[i].second], dp[p]);
            }
        }
        return ans;
    }
};
