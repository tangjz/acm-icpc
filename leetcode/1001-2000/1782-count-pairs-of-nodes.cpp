class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> deg(n);
        unordered_map<int, int> ctr;
        for(auto &it: edges) {
            int u = it[0] - 1, v = it[1] - 1;
            if(u > v)
                swap(u, v);
            ++deg[u];
            ++deg[v];
            ++ctr[u << 16 | v];
        }
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return deg[u] < deg[v];
        });
        vector<int> res;
        for(int lim: queries) {
            int ans = 0;
            for(int i = 0, j = n - 1; i < n; ++i) {
                for( ; j >= 0 && deg[ord[i]] + deg[ord[j]] > lim; --j);
                ans += n - max(i + 1, j + 1);
            }
            for(auto &it: ctr) {
                int state = it.first;
                int u = state >> 16, v = state & 65535;
                int w = it.second;
                ans -= deg[u] + deg[v] > lim && deg[u] + deg[v] - w <= lim;
            }
            res.push_back(ans);
        }
        return res;
    }
};
