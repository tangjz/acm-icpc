class Solution {
public:
    vector<int> groupStrings(vector<string>& words) {
        const int maxl = 26;
        int n = words.size();
        vector<int> seq(n);
        unordered_map<int, int> pos;
        for(int i = 0; i < n; ++i) {
            int &msk = seq[i] = 0;
            for(char ch: words[i])
                msk |= 1 << (ch - 'a');
            pos[msk] = i;
        }
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        unordered_map<int, int> vis;
        for(int i = 0; i < n; ++i) {
            int msk = seq[i];
            for(int j = 0; j < maxl; ++j) {
                if(!((msk >> j) & 1))
                    continue;
                int nxt = msk ^ (1 << j);
                auto it = pos.find(nxt);
                if(it != pos.end()) {
                    dsu_merge(i, it -> second);
                }
                auto jt = vis.find(nxt);
                if(jt != vis.end()) {
                    dsu_merge(i, jt -> second);
                } else {
                    vis.insert({nxt, i});
                }
            }
        }
        int ans = 0, best = 0;
        for(int i = 0; i < n; ++i)
            if(dsu_find(i) == i) {
                ++ans;
                best = max(best, -dsu[i]);
            }
        return {ans, best};
    }
};
