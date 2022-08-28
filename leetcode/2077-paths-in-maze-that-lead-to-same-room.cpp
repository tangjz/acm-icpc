class Solution {
public:
    int numberOfPaths(int n, vector<vector<int>>& edges) {
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[--it[0]].push_back(--it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<int> ord(n), rnk(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return make_pair(e[u].size(), u) > make_pair(e[v].size(), v);
        });
        for(int i = 0; i < n; ++i)
            rnk[ord[i]] = i;
        int ans = 0;
        vector<bool> vis(n);
        for(int u: ord) {
            for(int v: e[u])
                if(rnk[u] < rnk[v])
                    vis[v] = 1;
            for(int v: e[u])
                if(rnk[u] < rnk[v])
                    for(int w: e[v])
                        if(rnk[v] < rnk[w] && vis[w])
                            ++ans;
            for(int v: e[u])
                if(rnk[u] < rnk[v])
                    vis[v] = 0;
        }
        return ans;
    }
};
