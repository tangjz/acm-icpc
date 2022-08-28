class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size(), m = strs[0].size();
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) -> bool {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return 0;
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            return 1;
        };
        int ans = n;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                int ctr = 0, pos[3] = {};
                for(int k = 0; k < m && ctr <= 2; ++k)
                    if(strs[i][k] != strs[j][k])
                        pos[ctr++] = k;
                if(!ctr || ctr == 2 && strs[i][pos[0]] == strs[j][pos[1]] && strs[i][pos[1]] == strs[j][pos[0]])
                    ans -= dsu_merge(i, j);
            }
        return ans;
    }
};
