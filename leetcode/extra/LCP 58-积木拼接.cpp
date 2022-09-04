class Solution {
public:
    bool composeCube(vector<vector<string>>& shapes) {
        int n = shapes[0].size(), cnt = 0;
        for(auto &shape: shapes)
            for(auto &row: shape)
                for(char ch: row)
                    cnt += ch == '1';
        if(cnt != (n - 2) * 6 * n + 8)
            return 0;
        string zero;
        zero.assign(n * n * n, '0');
        auto gen = [&](vector<string> &shape) {
            vector<string> ret(48, zero);
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j) {
                    if(shape[i][j] == '0')
                        continue;
                    for(auto &[c0, p, q]: vector<array<int, 3> >{{0, i, j}, {1, i, n - 1 - j}})
                        for(auto &[c1, u, v]: vector<array<int, 3> >{{0, p, q}, {1, q, n - 1 - p}, {2, n - 1 - p, n - 1 - q}, {3, n - 1 - q, p}})
                            for(auto &[c2, x, y, z]: vector<array<int, 4> >{{0, u, v, 0}, {1, u, v, n - 1}, {2, u, 0, v}, {3, u, n - 1, v}, {4, 0, u, v}, {5, n - 1, u, v}})
                                ret[(c2 << 2 | c1) << 1 | c0][(x * n + y) * n + z] = '1';
                }
            return ret;
        };
        unordered_set<string> cur, nxt, vis;
        cur.insert(gen(shapes.back()).back());
        shapes.pop_back();
        while(!shapes.empty()) {
            nxt.clear();
            vis.clear();
            for(string u: gen(shapes.back())) {
                if(!vis.insert(u).second)
                    continue;
                for(string v: cur) {
                    bool bad = 0;
                    for(int i = 0; i < (int)v.size(); ++i)
                        if(u[i] == '1') {
                            if(v[i] == '1') {
                                bad = 1;
                                break;
                            }
                            v[i] = '1';
                        }
                    if(!bad)
                        nxt.insert(v);
                }
            }
            shapes.pop_back();
            cur.swap(nxt);
        }
        return !cur.empty();
    }
};
