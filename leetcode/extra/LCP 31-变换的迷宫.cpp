class Solution {
public:
    bool escapeMaze(vector<vector<string>>& maze) {
        int n = maze.size(), r = maze[0].size(), c = maze[0][0].size();
        vector<vector<int> > f(vector<vector<int> >(r, vector<int>(c)));
        f[0][0] = 1 << 0;
        for(int t = 1; t < n; ++t) {
            vector<vector<int> > g(vector<vector<int> >(r, vector<int>(c)));
            for(int i = 0; i < r; ++i)
                for(int j = 0; j < c; ++j) {
                    if(!f[i][j])
                        continue;
                    vector<pair<int, int> > cand;
                    for(int k = 0, tmp = f[i][j]; tmp > 0; ++k, tmp >>= 1)
                        if(tmp & 1)
                            cand.push_back({k >> 1, k & 1});
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!dx == !dy)
                                continue;
                            int ii = i + dx, jj = j + dy;
                            if(ii < 0 || ii >= r || jj < 0 || jj >= c)
                                continue;
                            bool ban = maze[t][ii][jj] == '#';
                            for(pair<int, int> it: cand) {
                                if(it.first == 1)
                                    it.first = 2;
                                if(!ban) {
                                    g[ii][jj] |= 1 << (it.first << 1 | it.second);
                                    continue;
                                }
                                if(it.first != 2)
                                    g[ii][jj] |= 1 << (1 << 1 | it.second);
                                if(!it.second)
                                    g[ii][jj] |= 1 << (it.first << 1 | 1);
                            }
                        }
                    bool ban = maze[t][i][j] == '#';
                    for(pair<int, int> it: cand) {
                        if(!ban) {
                            g[i][j] |= 1 << (it.first << 1 | it.second);
                            continue;
                        }
                        if(it.first != 2)
                            g[i][j] |= 1 << (1 << 1 | it.second);
                        if(!it.second)
                            g[i][j] |= 1 << (it.first << 1 | 1);
                    }
                }
            f = move(g);
        }
        return !!f[r - 1][c - 1];
    }
};
