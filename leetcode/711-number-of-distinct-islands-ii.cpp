class Solution {
    vector<pair<int, int> > minRep(vector<pair<int, int> > &rep) {
        vector<pair<int, int> > ret;
        for(int ref = 0; ref < 2; ++ref) {
            for(int rot = 0; rot < 4; ++rot) {
                pair<int, int> low = *min_element(rep.begin(), rep.end());
                for(auto &it: rep) {
                    it.first -= low.first;
                    it.second -= low.second;
                }
                sort(rep.begin(), rep.end());
                if(ret.empty() || rep < ret)
                    ret = rep;
                for(auto &it: rep)
                    it = {it.second, -it.first};
            }
            for(auto &it: rep)
                it.first = -it.first;
        }
        return ret;
    }
public:
    int numDistinctIslands2(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        set<vector<pair<int, int> > > sp;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(grid[i][j] != 1)
                    continue;
                vector<pair<int, int> > rep;
                queue<pair<int, int> > que;
                grid[i][j] = -1;
                rep.push_back({0, 0});
                que.push({i, j});
                while(!que.empty()) {
                    int ux, uy;
                    tie(ux, uy) = que.front();
                    que.pop();
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!dx == !dy)
                                continue;
                            int vx = ux + dx, vy = uy + dy;
                            if(vx < 0 || vx >= r || vy < 0 || vy >= c || grid[vx][vy] != 1)
                                continue;
                            grid[vx][vy] = -1;
                            rep.push_back({vx - i, vy - j});
                            que.push({vx, vy});
                        }
                }
                sp.insert(minRep(rep));
            }
        return sp.size();
    }
};
