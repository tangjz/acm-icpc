class Solution {
public:
    bool isCompliance(vector<vector<int>>& dis, int m) {
        int n = dis.size();
        vector<int> dsu(n, -1);
        function<int(int)> dsuFind = [&](int x) {
            if(dsu[x] < 0)
                return x;
            int t = dsu[x];
            dsu[x] = dsuFind(t);
            return dsu[x];
        };
        auto dsuMerge = [&](int u, int v) -> bool {
            int x = dsuFind(u), y = dsuFind(v);
            if(x == y)
                return 0;
            if(dsu[x] < dsu[y]) {
                swap(x, y);
                swap(u, v);
            }
            dsu[y] -= dsu[x] == dsu[y];
            dsu[x] = y;
            return 1;
        };
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                if(dis[i][j] <= 2)
                    dsuMerge(i, j);
        for(int i = 0; i < n; ++i)
            m -= dsuFind(i) == i;
        return m >= 0;
    }
};
