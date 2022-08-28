class Solution {
    int tarjan(int u, int p, int &ctr, vector<int> &dfn, vector<pair<int, int> > &path, vector<vector<int> > &e, vector<vector<int> > &bcc, vector<int> &idx) {
        int lowU = dfn[u] = ++ctr, sp = 0;
        for(int v: e[u]) {
            if(v == p)
                continue;
            if(dfn[v]) {
                lowU = min(lowU, dfn[v]);
                continue;
            }
            pair<int, int> cur = {u, v};
            path.push_back(cur);
            int lowV = tarjan(v, u, ctr, dfn, path, e, bcc, idx);
            lowU = min(lowU, lowV);
            if(lowV < dfn[u])
                continue;
            ++sp;
            if(p != -1 || sp > 1) {
                // printf("%d is cut\n", u);
                idx[u] = -2;
            }
            bcc.push_back({});
            int pos = bcc.size() - 1;
            pair<int, int> las = {-1, -1};
            auto &vec = bcc.back();
            // printf("bcc #%d:", pos);
            do {
                las = path.back();
                path.pop_back();
                for(int w: {las.first, las.second}) {
                    if(idx[w] == -1) {
                        idx[w] = pos;
                        vec.push_back(w);
                        // printf(" %d", w);
                    } else if(idx[w] == -2) {
                        vec.push_back(w);
                        // printf(" %d", w);
                    }
                }
            } while(las != cur);
            // puts("");
        }
        // printf("%d: low %d dfn %d\n", u, lowU, dfn[u]);
        return lowU;
    }
public:
    long long minimumCost(vector<int>& cost, vector<vector<int>>& roads) {
        int n = cost.size(), ctr = 0;
        vector<int> dfn(n), idx(n, -1);
        vector<pair<int, int> > path;
        vector<vector<int> > e(n), bcc;
        for(auto &it: roads) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        tarjan(0, -1, ctr, dfn, path, e, bcc, idx);
        vector<int> cand;
        for(int i = 0; i < (int)bcc.size(); ++i) {
            int low = INT_MAX;
            vector<int> adj;
            for(int u: bcc[i]) {
                if(idx[u] == -2) {
                    adj.push_back(-1 - u);
                    continue;
                }
                low = min(low, cost[u]);
            }
            // if(low == INT_MAX)
            //     continue;
            sort(adj.begin(), adj.end());
            adj.erase(unique(adj.begin(), adj.end()), adj.end());
            if((int)adj.size() == 1)
                cand.push_back(low);
            // printf("#%d: cost %d deg %d\n", i, low, (int)adj.size());
        }
        sort(cand.begin(), cand.end());
        if(cand.empty()) {
            cand.push_back(*min_element(cost.begin(), cost.end()));            
        } else {
            cand.pop_back();
        }
        long long ans = 0;
        for(int x: cand)
            ans += x;
        return ans;
    }
};
