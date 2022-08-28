class Solution {
public:
    vector<int> pondSizes(vector<vector<int>>& land) {
        int r = land.size(), c = land[0].size();
        vector<int> ret;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(land[i][j])
                    continue;
                ret.push_back(0);
                queue<pair<int, int> > que;
                land[i][j] = 1;
                que.push({i, j});
                while(!que.empty()) {
                    int ux, uy;
                    tie(ux, uy) = que.front();
                    ++ret.back();
                    que.pop();
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            int vx = ux + dx, vy = uy + dy;
                            if(vx < 0 || vx >= r || vy < 0 || vy >= c || land[vx][vy])
                                continue;
                            land[vx][vy] = 1;
                            que.push({vx, vy});
                        }
                }
            }
        sort(ret.begin(), ret.end());
        return ret;
    }
};
