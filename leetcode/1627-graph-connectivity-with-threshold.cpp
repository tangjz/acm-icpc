class Solution {
public:
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        vector<int> dsu(n + 1, -1);
        function<int(int)> dsuFind = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        for(int i = threshold + 1; i <= n; ++i)
            for(int j = i + i; j <= n; j += i) {
                int u = dsuFind(i), v = dsuFind(j);
                if(u == v)
                    continue;
                if(dsu[u] < dsu[v])
                    swap(u, v);
                dsu[v] -= dsu[u] == dsu[v];
                dsu[u] = v;
            }
        vector<bool> ret;
        for(auto &it: queries)
            ret.push_back(dsuFind(it[0]) == dsuFind(it[1]));
        return ret;
    }
};
