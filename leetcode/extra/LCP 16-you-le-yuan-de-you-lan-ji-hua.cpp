class Solution {
public:
    int maxWeight(vector<vector<int>>& edges, vector<int>& value) {
        int n = value.size();
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<int> ord(n), rnk(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return make_pair(e[u].size(), u) < make_pair(e[v].size(), v);
        });
        for(int i = 0; i < n; ++i)
            rnk[ord[i]] = i;
        typedef long long LL;
        vector<vector<vector<int> > > cand(n);
        unordered_map<LL, pair<int, int> > best;
        auto upd1 = [&](int u, int v, int w) {
            vector<int> vec = {value[v] + value[w], v, w};
            for(auto &it: cand[u])
                if(vec > it)
                    vec.swap(it);
            if(cand[u].size() < 6)
                cand[u].push_back(move(vec));
        };
        auto upd2 = [&](int u, int v, int w) {
            LL msk = u * n + v;
            int val = value[w];
            pair<int, int> &ret = best[msk];
            if(val > ret.first)
                swap(val, ret.first);
            if(val > ret.second)
                swap(val, ret.second);
        };
        vector<int> vis(n);
        for(int u: ord) {
            for(int v: e[u])
                if(rnk[u] > rnk[v])
                    vis[v] = 1;
            for(int v: e[u]) {
                if(rnk[u] < rnk[v])
                    continue;
                for(int w: e[v]) {
                    if(rnk[v] < rnk[w] || !vis[w])
                        continue;
                    upd1(u, v, w);
                    upd1(v, u, w);
                    upd1(w, u, v);
                    upd2(u, v, w);
                    upd2(u, w, v);
                    upd2(v, w, u);
                }
            }
            for(int v: e[u])
                if(rnk[u] > rnk[v])
                    vis[v] = 0;
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            int sz = cand[i].size();
            for(int j = 0; j < sz; ++j)
                for(int k = j + 1; k < sz; ++k) {
                    auto &it = cand[i][j], &jt = cand[i][k];
                    if(it[1] == jt[1] || it[1] == jt[2] || it[2] == jt[1] || it[2] == jt[2])
                        continue;
                    ans = max(ans, value[i] + it[0] + jt[0]);
                }
        }
        for(auto &it: best) {
            int u = it.first / n, v = it.first % n;
            ans = max(ans, value[u] + value[v] + it.second.first + it.second.second);
        }
        return ans;
    }
};
