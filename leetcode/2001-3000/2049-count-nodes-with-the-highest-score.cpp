class Solution {
public:
    int countHighestScoreNodes(vector<int>& par) {
        typedef long long LL;
        int n = par.size();
        vector<int> sz(n), ord;
        vector<vector<int> > e(n);
        for(int i = 1; i < n; ++i) {
            e[par[i]].push_back(i);
        }
        ord.push_back(0);
        for(int i = 0; i < n; ++i) {
            int u = ord[i];
            for(int v: e[u]) {
                ord.push_back(v);
            }
        }
        LL best = 0;
        int cnt = 0;
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i], p = par[u];
            LL prd = 1;
            ++sz[u];
            for(int v: e[u]) {
                prd *= sz[v];
                sz[u] += sz[v];
            }
            if(sz[u] < n) {
                prd *= n - sz[u];
            }
            if(prd > best) {
                best = prd;
                cnt = 0;
            }
            cnt += prd == best;
        }
        return cnt;
    }
};
