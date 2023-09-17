class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size(), rt = -1;
        vector<vector<int> > e(n);
        for(int i = 0; i < n; ++i)
            if(coins[i]) {
                rt = i;
                break;
            }
        if(rt == -1)
            return 0;
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<int> par(n, -1), seq(n), sub(n, -1);
        vector<bool> vis(n);
        vis[rt] = 1;
        seq[0] = rt;
        auto upd = [&](int u, int v) {
            if(sub[u] == -1) {
                sub[u] = v;
            } else if(sub[u] != v) {
                sub[u] = -2;
            }
        };
        for(int i = 0, tot = 1; i < tot; ++i) {
            int u = seq[i], p = par[u], pp = p == -1 ? -1 : par[p];
            if(coins[u]) {
                if(pp != -1) {
                    vis[pp] = 1;
                    upd(p, u);
                    upd(pp, p);
                } else if(p == rt) {
                    upd(p, u);
                }
            }
            for(int v: e[u])
                if(v != p) {
                    par[v] = u;
                    seq[tot++] = v;
                }
        }
        for(int i = n - 1; i >= 0; --i) {
            int u = seq[i], p = par[u];
            if(p != -1 && vis[u]) {
                vis[p] = 1;
                upd(p, u);
            }
        }
        // printf("rt %d sub %d\n", rt, sub[rt]);
        if(sub[rt] >= 0) {
            vis[rt] = 0;
            rt = sub[rt];
            vis[rt] = 1;
            // printf("change #1 rt %d sub %d\n", rt, sub[rt]);
        }
        if(sub[rt] >= 0) {
            vis[rt] = 0;
            rt = sub[rt];
            vis[rt] = 1;
            // printf("change #2 rt %d sub %d\n", rt, sub[rt]);
        } else if(sub[rt] == -2) {
            int sp = -1, fir = -1;
            for(int v: e[rt]) {
                if(v == par[rt])
                    continue;
                // printf("v %d sub %d\n", v, sub[v]);
                if(!coins[v] && sub[v] == -1)
                    continue;
                if(fir == -1)
                    fir = v;
                if(sub[v] == -1)
                    continue;
                if(sp == -1) {
                    sp = v;
                } else {
                    sp = -2;
                }
            }
            // printf("n %d rt %d sp %d fir %d\n", n, rt, sp, fir);
            if(sp == -1)
                sp = fir;
            if(sp >= 0) {
                vis[rt] = 0;
                rt = sp;
                vis[rt] = 1;
                // printf("change #2 rt %d sub %d\n", rt, sub[rt]);
            }
        }
        int ans = -1;
        for(int i = 0; i < n; ++i)
            ans += vis[i];
        return ans * 2;
    }
};
