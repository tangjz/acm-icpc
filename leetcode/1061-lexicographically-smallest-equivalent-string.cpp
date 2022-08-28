class Solution {
public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        const int maxd = 26;
        vector<int> dsu(maxd, -1), low(maxd);
        iota(low.begin(), low.end(), 0);
        function<int(int)> dsu_find = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) -> bool {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return 0;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            low[v] = min(low[v], low[u]);
            return 1;
        };
        int n = s1.size();
        for(int i = 0; i < n; ++i)
            dsu_merge(s1[i] - 'a', s2[i] - 'a');
        for(char &ch: baseStr)
            ch = 'a' + low[dsu_find(ch - 'a')];
        return baseStr;
    }
};
