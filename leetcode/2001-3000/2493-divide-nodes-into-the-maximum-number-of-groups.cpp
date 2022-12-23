class Solution {
public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[--it[0]].push_back(--it[1]);
            e[it[1]].push_back(it[0]);
        }
        int ans = 0, tot = 0;
        vector<int> que(n), col(n, -1), que2(n), dep(n, -1), vis(n, -1);
        auto calc = [&]() {
            int res = 0;
            for(int i = 0; i < tot; ++i) {
                int tot2 = 0, tim = que[i];
                vis[que[i]] = tim;
                dep[que[i]] = 1;
                que2[tot2++] = que[i];
                for(int j = 0; j < tot2; ++j) {
                    int u = que2[j];
                    for(int v: e[u]) {
                        if(vis[v] == tim)
                            continue;
                        vis[v] = tim;
                        dep[v] = dep[u] + 1;
                        que2[tot2++] = v;
                    }
                }
                res = max(res, dep[que2[tot2 - 1]]);
            }
            return res;
        };
        for(int i = 0; i < n; ++i) {
            if(col[i] != -1)
                continue;
            tot = 0;
            dep[i] = 1;
            col[i] = 0;
            que[tot++] = i;
            for(int j = 0; j < tot; ++j) {
                int u = que[j];
                for(int v: e[u])
                    if(col[v] == -1) {
                        col[v] = !col[u];
                        que[tot++] = v;
                    } else if(col[u] == col[v]) {
                        return -1;
                    }
            }
            ans += calc();
        }
        return ans;
    }
};
