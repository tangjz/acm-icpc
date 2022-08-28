class DistanceLimitedPathsExist {
    vector<pair<int, int> > dsu;
    
    int dsuFind(int x) {
        for( ; dsu[x].first >= 0; x = dsu[x].first);
        return x;
    }
    
    void dsuMerge(int u, int v, int w) {
        u = dsuFind(u);
        v = dsuFind(v);
        if(u == v)
            return;
        if(dsu[u].first < dsu[v].first)
            swap(u, v);
        dsu[v].first -= dsu[u].first == dsu[v].first;
        dsu[u] = {v, w};
    }
public:
    DistanceLimitedPathsExist(int n, vector<vector<int>>& edges) {
        dsu.resize(n, {-1, 0});
        sort(edges.begin(), edges.end(), [&](auto const &u, auto const &v) {
            return u[2] < v[2];
        });
        for(auto &it: edges)
            dsuMerge(it[0], it[1], it[2]);
    }
    
    bool query(int p, int q, int limit) {
        for( ; dsu[p].first >= 0 && dsu[p].second < limit; p = dsu[p].first);
        for( ; dsu[q].first >= 0 && dsu[q].second < limit; q = dsu[q].first);
        return p == q;
    }
};

/**
 * Your DistanceLimitedPathsExist object will be instantiated and called as such:
 * DistanceLimitedPathsExist* obj = new DistanceLimitedPathsExist(n, edgeList);
 * bool param_1 = obj->query(p,q,limit);
 */
