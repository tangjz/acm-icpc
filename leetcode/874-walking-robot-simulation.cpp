class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        int ans = 0, x = 0, y = 0, d = 0;
        set<pair<int, int> > ban;
        for(auto &it: obstacles)
            ban.insert({it[0], it[1]});
        for(int k: commands)
            if(k < 0) {
                d = (d + (k == -1 ? 1 : 3)) & 3;
            } else {
                while(k--) {
                    int xx = x + dx[d], yy = y + dy[d];
                    if(ban.count({xx, yy}))
                        break;
                    tie(x, y) = {xx, yy};
                    ans = max(ans, x * x + y * y);
                }
            }
        return ans;
    }
};
