class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        const int maxn = 8;
        vector<vector<bool> > vis(maxn, vector<bool>(maxn));
        for(auto &it: queens)
            vis[it[0]][it[1]] = 1;
        vector<vector<int> > ans;
        for(int dx = -1; dx <= 1; ++dx)
            for(int dy = -1; dy <= 1; ++dy) {
                if(!dx && !dy)
                    continue;
                for(int x = king[0] + dx, y = king[1] + dy; x >= 0 && x < maxn && y >= 0 && y < maxn; x += dx, y += dy) {
                    if(vis[x][y]) {
                        ans.push_back({x, y});
                        break;
                    }
                }
            }
        return ans;
    }
};
