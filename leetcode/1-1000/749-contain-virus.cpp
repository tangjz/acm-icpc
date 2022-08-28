class Solution {
public:
    int containVirus(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size(), ans = 0;
        vector<vector<int> > pos(r, vector<int>(c));
        while(true) {
            for(int i = 0; i < r; ++i)
                pos[i].assign(c, -1);
            vector<int> cost;
            vector<set<pair<int, int> > > adj;
            vector<vector<pair<int, int> > > que;
            int best = -1;
            for(int i = 0; i < r; ++i)
                for(int j = 0; j < c; ++j) {
                    if(mat[i][j] != 1 || pos[i][j] != -1)
                        continue;
                    int id = adj.size();
                    adj.push_back({});
                    que.push_back({});
                    pos[i][j] = id;
                    que.back().push_back({i, j});
                    cost.push_back(0);
                    int &ctr = cost.back();
                    for(int k = 0; k < (int)que.back().size(); ++k) {
                        int ux, uy;
                        tie(ux, uy) = que.back()[k];
                        for(int dx = -1; dx <= 1; ++dx)
                            for(int dy = -1; dy <= 1; ++dy) {
                                if(!dx == !dy)
                                    continue;
                                int vx = ux + dx, vy = uy + dy;
                                if(vx < 0 || vx >= r || vy < 0 || vy >= c)
                                    continue;
                                if(mat[vx][vy] != 1) {
                                    if(!mat[vx][vy]) {
                                        ++ctr;
                                        adj.back().insert({vx, vy});
                                    }
                                    continue;
                                }
                                if(pos[vx][vy] == -1) {
                                    pos[vx][vy] = id;
                                    que.back().push_back({vx, vy});
                                }
                            }
                    }
                    best = max(best, (int)adj.back().size());
                }
            if(best <= 0)
                break;
            for(int i = 0; i < (int)adj.size(); ++i) {
                if(best == (int)adj[i].size()) {
                    best = -1;
                    ans += cost[i];
                    for(auto &it: que[i])
                        mat[it.first][it.second] = -1;
                    continue;
                }
                for(auto &it: adj[i])
                    mat[it.first][it.second] = 1;
            }
        }
        return ans;
    }
};
