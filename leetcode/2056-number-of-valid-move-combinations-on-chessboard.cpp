class Solution {
public:
    int countCombinations(vector<string>& typ, vector<vector<int>>& pos) {
        const int dt[8][2] = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0},
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
        };
        int n = typ.size();
        set<vector<int> > Hash;
        vector<int> dirs(n);
        function<void(int, vector<int> &)> dfs2 = [&](int msk, vector<int> &pos) {
            Hash.insert(pos);
            int rem = ((1 << n) - 1) ^ msk;
            if(!rem)
                return;
            for(int adt = rem; ; adt = (adt - 1) & rem) {
                int nxt = msk | adt;
                bool ok = 1;
                set<pair<int, int> > vis;
                for(int i = 0; i < n; ++i) {
                    int &x = pos[i << 1], &y = pos[i << 1 | 1];
                    if(!((nxt >> i) & 1)) {
                        x += dt[dirs[i]][0];
                        y += dt[dirs[i]][1];
                        if(min(x, y) <= 0 || max(x, y) > 8) {
                            ok = 0;
                        }
                    }
                    auto it = make_pair(x, y);
                    if(vis.count(it)) {
                        ok = 0;
                    }
                    vis.insert(it);
                }
                if(ok)
                    dfs2(nxt, pos);
                for(int i = 0; i < n; ++i) {
                    int &x = pos[i << 1], &y = pos[i << 1 | 1];
                    if(!((nxt >> i) & 1)) {
                        x -= dt[dirs[i]][0];
                        y -= dt[dirs[i]][1];
                    }
                }
                if(!adt)
                    break;
            }
        };
        function<void(int)> dfs1 = [&](int dep) {
            if(dep == n) {
                vector<int> curPos;
                for(auto &it: pos) {
                    curPos.push_back(it[0]);
                    curPos.push_back(it[1]);
                }
                dfs2(0, curPos);
                return;
            }
            if(typ[dep] != "bishop")
                for(int i = 0; i < 4; ++i) {
                    dirs[dep] = i;
                    dfs1(dep + 1);
                }
            if(typ[dep] != "rook")
                for(int i = 4; i < 8; ++i) {
                    dirs[dep] = i;
                    dfs1(dep + 1);
                }
        };
        dfs1(0);
        return Hash.size();
    }
};
