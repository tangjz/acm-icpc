class Solution {
    int getID(unordered_map<int, int> &Hash, int x) {
        auto it = Hash.find(x);
        if(it != Hash.end())
            return it -> second;
        int tot = (int)Hash.size();
        return Hash[x] = tot;
    }
public:
    int checkWays(vector<vector<int>>& pairs) {
        vector<int> deg;
        unordered_map<int, int> points;
        for(auto &it : pairs) {
            int u = getID(points, it[0]);
            int v = getID(points, it[1]);
            if(u > v)
                swap(u, v);
            if(v >= (int)deg.size())
                deg.resize(v + 1);
            ++deg[u];
            ++deg[v];
        }
        int n = (int)deg.size();
        vector<int> ord(n), rnk(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return make_pair(deg[u], u) < make_pair(deg[v], v);
        });
        for(int i = 0; i < n; ++i)
            rnk[ord[i]] = i;
        vector<vector<int> > edges(n, vector<int>(n)), sub(n, vector<int>(n));
        for(auto &it : pairs) {
            int u = getID(points, it[0]);
            int v = getID(points, it[1]);
            if(rnk[u] < rnk[v])
                swap(u, v);
            sub[u][v] = 1;
            edges[u][v] = edges[v][u] = 1;
        }
        bool isUnique = 1;
        vector<int> par(n, -1);
        for(int v = 0; v < n; ++v) {
            for(int u = 0; u < n; ++u)
                if(sub[u][v] && (par[v] == -1 || rnk[u] < rnk[par[v]]))
                    par[v] = u;
            if(par[v] != -1) {
                isUnique &= deg[v] < deg[par[v]];
            } else if(deg[v] != n - 1) {
                return 0;
            }
        }
        for(int i = 0; i < n; ++i)
            for(int p = par[i]; p != -1; p = par[p]) {
                if(!edges[p][i] || !edges[i][p])
                    return 0;
                edges[p][i] = edges[i][p] = 0;
            }
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                if(edges[i][j])
                    return 0;
        return isUnique ? 1 : 2;
    }
};
