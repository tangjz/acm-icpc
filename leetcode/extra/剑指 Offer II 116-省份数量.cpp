class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = (int)M.size();
        if(!n)
            return 0;
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        for(int i = 0; i < n; ++i) {
            auto &row = M[i];
            for(int j = 0; j < i; ++j) {
                if(row[j] != 1)
                    continue;
                int u = dsu_find(i), v = dsu_find(j);
                if(u == v)
                    continue;
                if(dsu[u] < dsu[v])
                    swap(u, v);
                dsu[v] -= dsu[u] == dsu[v];
                dsu[u] = v;
            }
        }
        int cnt = 0;
        for(int i = 0; i < n; ++i)
            cnt += dsu_find(i) == i;
        return cnt;
    }
};
