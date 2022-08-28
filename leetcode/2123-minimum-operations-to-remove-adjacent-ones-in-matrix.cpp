class Solution {
    bool path(int u, vector<vector<int> > &e, int &st, vector<int> &vis, vector<int> &match) {
        for(int v: e[u]) {
            if(vis[v] == st)
                continue;
            vis[v] = st;
            if(match[v] == -1 || path(match[v], e, st, vis, match)) {
                match[v] = u;
                return 1;
            }
        }
        return 0;
    };
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), n = 0, m = 0;
        vector<vector<int> > e;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(!grid[i][j])
                    continue;
                bool lft = (i & 1) == (j & 1);
                grid[i][j] = lft ? (++n) : (++m);
                if(lft)
                    e.push_back({});
                if(i > 0 && grid[i - 1][j]) {
                    int u = grid[i - 1][j], v = grid[i][j];
                    if(lft)
                        swap(u, v);
                    e[--u].push_back(--v);
                }
                if(j > 0 && grid[i][j - 1]) {
                    int u = grid[i][j - 1], v = grid[i][j];
                    if(lft)
                        swap(u, v);
                    e[--u].push_back(--v);
                }
            }
        mt19937 rnd(time(nullptr));
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        shuffle(ord.begin(), ord.end(), rnd);
        for(int i = 0; i < n; ++i)
            shuffle(e[i].begin(), e[i].end(), rnd);
        int st = 0;
        vector<int> match(m, -1), vis(m);
        int ans = 0;
        for(int i: ord) {
            ++st;
            ans += path(i, e, st, vis, match);
        }
        return ans;
    }
};
