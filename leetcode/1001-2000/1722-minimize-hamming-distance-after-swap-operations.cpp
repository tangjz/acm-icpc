class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = (int)source.size();
        vector<int> dsu(n, -1);
        function<int(int)> dsuFind = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        auto dsuMerge = [&](int u, int v) -> void {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
        };
        for(auto &it: allowedSwaps)
            dsuMerge(it[0], it[1]);
        map<int, map<int, int> > ctr;
        for(int i = 0; i < n; ++i) {
            int p = dsuFind(i);
            ++ctr[p][source[i]];
            --ctr[p][target[i]];
        }
        int ans = 0;
        for(auto &it : ctr)
            for(auto &jt : it.second)
                ans += abs(jt.second);
        return ans / 2;
    }
};
