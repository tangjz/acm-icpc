class BlackBox {
    vector<pair<int, int> > pos[2];
    vector<vector<pair<int, int> > > cyc;
    vector<set<int> > vis;
public:
    BlackBox(int n, int m) {
        int tot = (n + m) * 2;
        pos[0].assign(tot, {-1, -1});
        pos[1].assign(tot, {-1, -1});
        auto check = [&](int dir, int idx) {
            int p = cyc.size(), q = 0;
            vector<pair<int, int> > vec;
            while(pos[dir > 0][idx].first == -1) {
                pos[dir > 0][idx] = {p, q++};
                vec.push_back({dir, idx});
                idx = dir > 0 ? tot - idx : m + m - idx;
                idx < 0 && (idx += tot);
                if(idx % (tot >> 1) != 0 && idx % (tot >> 1) != m)
                    dir = -dir;
            }
            cyc.push_back(vec);
            vis.push_back({});
        };
        for(int i = 0; i < tot; ++i) {
            if(i % (tot >> 1) != 0 && pos[1][i].first == -1)
                check(1, i);
            if(i % (tot >> 1) != m && pos[0][i].first == -1)
                check(-1, i);
        }
    }

    int open(int index, int direction) {
        for(int dir = -1; dir <= 1; dir += 2) {
            auto &it = pos[dir > 0][index];
            if(it.first != -1)
                vis[it.first].insert(it.second);
        }
        auto &it = pos[direction > 0][index];
        auto jt = vis[it.first].upper_bound(it.second);
        if(jt == vis[it.first].end())
            jt = vis[it.first].begin();
        return cyc[it.first][*jt].second;
    }

    void close(int index) {
        for(int dir = -1; dir <= 1; dir += 2) {
            auto &it = pos[dir > 0][index];
            if(it.first != -1)
                vis[it.first].erase(it.second);
        }
    }
};

/**
 * Your BlackBox object will be instantiated and called as such:
 * BlackBox* obj = new BlackBox(n, m);
 * int param_1 = obj->open(index,direction);
 * obj->close(index);
 */
