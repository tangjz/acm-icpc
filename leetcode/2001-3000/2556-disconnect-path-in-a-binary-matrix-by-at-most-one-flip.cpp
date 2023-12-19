class Solution {
public:
    bool isPossibleToCutPath(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size();
        vector<vector<bool> > vis(r, vector<bool>(c));
        queue<pair<int, int> > que;
        auto upd = [&](int x, int y) {
            if(x < 0 || x >= r || y < 0 || y >= c || !mat[x][y] || vis[x][y])
                return;
            vis[x][y] = 1;
            que.push({x, y});
        };
        upd(r - 1, c - 1);
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            upd(x, y - 1);
            upd(x - 1, y);
        }
        if(!vis[0][0])
            return 1;
        pair<int, int> u = {}, v = {};
        for(int i = 0; i < r + c - 2; ++i) {
            if(i > 0 && u == v)
                return 1;
            if(u.first + 1 < r && vis[u.first + 1][u.second]) {
                ++u.first;
            } else {
                ++u.second;
            }
            if(v.second + 1 < c && vis[v.first][v.second + 1]) {
                ++v.second;
            } else {
                ++v.first;
            }
        }
        return 0;
    }
};
