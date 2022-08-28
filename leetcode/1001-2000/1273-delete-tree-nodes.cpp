class Solution {
public:
    int deleteTreeNodes(int n, vector<int>& par, vector<int>& val) {
        vector<vector<int> > e(n);
        vector<int> ord = {0}, s(n), f(n);
        for(int i = 1; i < n; ++i)
            e[par[i]].push_back(i);
        for(int i = 0; i < n; ++i) {
            int u = ord[i];
            for(int v: e[u])
                ord.push_back(v);
        }
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i], p = par[u];
            ++f[u];
            if(!(s[u] += val[u]))
                f[u] = 0;
            if(p >= 0) {
                s[p] += s[u];
                f[p] += f[u];
            }
        }
        return f[0];
    }
};
