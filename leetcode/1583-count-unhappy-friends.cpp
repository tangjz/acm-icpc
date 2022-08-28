class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        vector<vector<int> > rnk(n, vector<int>(n, -1));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n - 1; ++j)
                rnk[i][preferences[i][j]] = j;
        auto upd = [&](bool &vis, int x, int y, int u, int v) {
            if(!vis && rnk[x][u] < rnk[x][y] && rnk[u][x] < rnk[u][v])
                vis = 1;
        };
        int ans = 0, m = n / 2;
        for(int i = 0; i < m; ++i) {
            bool lft = 0, rht = 0;
            for(int j = 0; j < m; ++j) {
                if(i == j)
                    continue;
                upd(lft, pairs[i][0], pairs[i][1], pairs[j][0], pairs[j][1]);
                upd(lft, pairs[i][0], pairs[i][1], pairs[j][1], pairs[j][0]);
                upd(rht, pairs[i][1], pairs[i][0], pairs[j][0], pairs[j][1]);
                upd(rht, pairs[i][1], pairs[i][0], pairs[j][1], pairs[j][0]);
            }
            ans += lft;
            ans += rht;
        }
        return ans;
    }
};
