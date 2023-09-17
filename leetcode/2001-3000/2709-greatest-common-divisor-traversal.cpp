class Solution {
public:
    bool canTraverseAllPairs(vector<int>& A) {
        static const int maxv = (int)1e5 + 1, maxs = (int)2e5 + 1;
        static int ptot = 0, d[maxv] = {}, pr[maxv];
        static int st = 0, tim[maxs] = {}, dsu[maxs];
        if(!ptot) {
            for(int i = 2; i < maxv; ++i) {
                if(!d[i])
                    pr[ptot++] = d[i] = i;
                for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
                    d[k] = pr[j];
                    if(d[i] == pr[j])
                        break;
                }
            }
        }
        int n = A.size();
        if(!(++st)) {
            memset(tim, 0, sizeof tim);
            ++st;
        }
        function<int(int)> dsuFind = [&](int u) {
            return dsu[u] < 0 ? u : (dsu[u] = dsuFind(dsu[u]));
        };
        auto dsuMerge = [&](int u, int v) {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        for(int i = 0, u = maxv; i < n; ++i, ++u) {
            tim[u] = st;
            dsu[u] = -1;
            for(int tmp = A[i], p; tmp > 1; ) {
                p = d[tmp];
                if(tim[p] != st) {
                    tim[p] = st;
                    dsu[p] = -1;
                }
                dsuMerge(u, p);
                for( ; d[tmp] == p; tmp /= p);
            }
        }
        for(int i = 1, u = maxv + 1, rt = dsuFind(maxv); i < n; ++i, ++u)
            if(dsuFind(u) != rt)
                return 0;
        return 1;
    }
};
